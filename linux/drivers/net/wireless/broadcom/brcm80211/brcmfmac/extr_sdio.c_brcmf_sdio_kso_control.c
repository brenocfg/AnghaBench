#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct brcmf_sdio {TYPE_2__* sdiodev; TYPE_1__* ci; } ;
struct TYPE_5__ {int /*<<< orphan*/  func1; } ;
struct TYPE_4__ {scalar_t__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_SDIO_MAX_ACCESS_ERRORS ; 
 scalar_t__ CY_CC_43012_CHIP_ID ; 
 int /*<<< orphan*/  KSO_WAIT_US ; 
 int MAX_KSO_ATTEMPTS ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_SLEEPCSR ; 
 int SBSDIO_FUNC1_SLEEPCSR_DEVON_MASK ; 
 int SBSDIO_FUNC1_SLEEPCSR_KSO_MASK ; 
 int SBSDIO_FUNC1_SLEEPCSR_KSO_SHIFT ; 
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  brcmf_err (char*,int,int) ; 
 int brcmf_sdiod_readb (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (TYPE_2__*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  sdio_retune_crc_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_retune_crc_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_retune_hold_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_retune_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
brcmf_sdio_kso_control(struct brcmf_sdio *bus, bool on)
{
	u8 wr_val = 0, rd_val, cmp_val, bmask;
	int err = 0;
	int err_cnt = 0;
	int try_cnt = 0;

	brcmf_dbg(TRACE, "Enter: on=%d\n", on);

	sdio_retune_crc_disable(bus->sdiodev->func1);

	/* Cannot re-tune if device is asleep; defer till we're awake */
	if (on)
		sdio_retune_hold_now(bus->sdiodev->func1);

	wr_val = (on << SBSDIO_FUNC1_SLEEPCSR_KSO_SHIFT);
	/* 1st KSO write goes to AOS wake up core if device is asleep  */
	brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR, wr_val, &err);

	/* In case of 43012 chip, the chip could go down immediately after
	 * KSO bit is cleared. So the further reads of KSO register could
	 * fail. Thereby just bailing out immediately after clearing KSO
	 * bit, to avoid polling of KSO bit.
	 */
	if (!on && bus->ci->chip == CY_CC_43012_CHIP_ID)
		return err;

	if (on) {
		/* device WAKEUP through KSO:
		 * write bit 0 & read back until
		 * both bits 0 (kso bit) & 1 (dev on status) are set
		 */
		cmp_val = SBSDIO_FUNC1_SLEEPCSR_KSO_MASK |
			  SBSDIO_FUNC1_SLEEPCSR_DEVON_MASK;
		bmask = cmp_val;
		usleep_range(2000, 3000);
	} else {
		/* Put device to sleep, turn off KSO */
		cmp_val = 0;
		/* only check for bit0, bit1(dev on status) may not
		 * get cleared right away
		 */
		bmask = SBSDIO_FUNC1_SLEEPCSR_KSO_MASK;
	}

	do {
		/* reliable KSO bit set/clr:
		 * the sdiod sleep write access is synced to PMU 32khz clk
		 * just one write attempt may fail,
		 * read it back until it matches written value
		 */
		rd_val = brcmf_sdiod_readb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR,
					   &err);
		if (!err) {
			if ((rd_val & bmask) == cmp_val)
				break;
			err_cnt = 0;
		}
		/* bail out upon subsequent access errors */
		if (err && (err_cnt++ > BRCMF_SDIO_MAX_ACCESS_ERRORS))
			break;

		udelay(KSO_WAIT_US);
		brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR, wr_val,
				   &err);

	} while (try_cnt++ < MAX_KSO_ATTEMPTS);

	if (try_cnt > 2)
		brcmf_dbg(SDIO, "try_cnt=%d rd_val=0x%x err=%d\n", try_cnt,
			  rd_val, err);

	if (try_cnt > MAX_KSO_ATTEMPTS)
		brcmf_err("max tries: rd_val=0x%x err=%d\n", rd_val, err);

	if (on)
		sdio_retune_release(bus->sdiodev->func1);

	sdio_retune_crc_enable(bus->sdiodev->func1);

	return err;
}