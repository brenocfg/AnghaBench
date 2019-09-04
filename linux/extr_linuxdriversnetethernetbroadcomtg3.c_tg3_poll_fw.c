#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tg3 {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5906 ; 
 scalar_t__ CHIPREV_ID_57765_A0 ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_SSB_CORE ; 
 int /*<<< orphan*/  NIC_SRAM_FIRMWARE_MBOX ; 
 int /*<<< orphan*/  NIC_SRAM_FIRMWARE_MBOX_MAGIC1 ; 
 int /*<<< orphan*/  NO_FWARE_REPORTED ; 
 int /*<<< orphan*/  VCPU_STATUS ; 
 int VCPU_STATUS_INIT_DONE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 scalar_t__ tg3_chip_rev_id (struct tg3*) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_read_mem (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tg3_poll_fw(struct tg3 *tp)
{
	int i;
	u32 val;

	if (tg3_flag(tp, NO_FWARE_REPORTED))
		return 0;

	if (tg3_flag(tp, IS_SSB_CORE)) {
		/* We don't use firmware. */
		return 0;
	}

	if (tg3_asic_rev(tp) == ASIC_REV_5906) {
		/* Wait up to 20ms for init done. */
		for (i = 0; i < 200; i++) {
			if (tr32(VCPU_STATUS) & VCPU_STATUS_INIT_DONE)
				return 0;
			if (pci_channel_offline(tp->pdev))
				return -ENODEV;

			udelay(100);
		}
		return -ENODEV;
	}

	/* Wait for firmware initialization to complete. */
	for (i = 0; i < 100000; i++) {
		tg3_read_mem(tp, NIC_SRAM_FIRMWARE_MBOX, &val);
		if (val == ~NIC_SRAM_FIRMWARE_MBOX_MAGIC1)
			break;
		if (pci_channel_offline(tp->pdev)) {
			if (!tg3_flag(tp, NO_FWARE_REPORTED)) {
				tg3_flag_set(tp, NO_FWARE_REPORTED);
				netdev_info(tp->dev, "No firmware running\n");
			}

			break;
		}

		udelay(10);
	}

	/* Chip might not be fitted with firmware.  Some Sun onboard
	 * parts are configured like that.  So don't signal the timeout
	 * of the above loop as an error, but do report the lack of
	 * running firmware once.
	 */
	if (i >= 100000 && !tg3_flag(tp, NO_FWARE_REPORTED)) {
		tg3_flag_set(tp, NO_FWARE_REPORTED);

		netdev_info(tp->dev, "No firmware running\n");
	}

	if (tg3_chip_rev_id(tp) == CHIPREV_ID_57765_A0) {
		/* The 57765 A0 needs a little more
		 * time to do some important work.
		 */
		mdelay(10);
	}

	return 0;
}