#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct brcmf_sdio_dev {TYPE_1__* func1; } ;
struct TYPE_4__ {int f1regdata; int /*<<< orphan*/  fc_rcvd; int /*<<< orphan*/  fc_xon; int /*<<< orphan*/  fc_xoff; } ;
struct brcmf_sdio {int rx_seq; int rxskip; int sdpcm_ver; int flowcontrol; TYPE_2__ sdcnt; struct brcmf_core* sdio_core; struct brcmf_sdio_dev* sdiodev; } ;
struct brcmf_core {scalar_t__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HMB_DATA_DEVREADY ; 
 int HMB_DATA_FC ; 
 int HMB_DATA_FCDATA_MASK ; 
 int HMB_DATA_FCDATA_SHIFT ; 
 int HMB_DATA_FWHALT ; 
 int HMB_DATA_FWREADY ; 
 int HMB_DATA_NAKHANDLED ; 
 int HMB_DATA_VERSION_MASK ; 
 int HMB_DATA_VERSION_SHIFT ; 
 int I_HMB_FRAME_IND ; 
 int /*<<< orphan*/  SDIO ; 
 int SDPCM_PROT_VERSION ; 
 scalar_t__ SD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMB_INT_ACK ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 int /*<<< orphan*/  brcmf_fw_crashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_sdio_get_console_addr (struct brcmf_sdio*) ; 
 int brcmf_sdiod_readl (struct brcmf_sdio_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writel (struct brcmf_sdio_dev*,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tohostmailboxdata ; 
 int /*<<< orphan*/  tosbmailbox ; 

__attribute__((used)) static u32 brcmf_sdio_hostmail(struct brcmf_sdio *bus)
{
	struct brcmf_sdio_dev *sdiod = bus->sdiodev;
	struct brcmf_core *core = bus->sdio_core;
	u32 intstatus = 0;
	u32 hmb_data;
	u8 fcbits;
	int ret;

	brcmf_dbg(SDIO, "Enter\n");

	/* Read mailbox data and ack that we did so */
	hmb_data = brcmf_sdiod_readl(sdiod,
				     core->base + SD_REG(tohostmailboxdata),
				     &ret);

	if (!ret)
		brcmf_sdiod_writel(sdiod, core->base + SD_REG(tosbmailbox),
				   SMB_INT_ACK, &ret);

	bus->sdcnt.f1regdata += 2;

	/* dongle indicates the firmware has halted/crashed */
	if (hmb_data & HMB_DATA_FWHALT) {
		brcmf_dbg(SDIO, "mailbox indicates firmware halted\n");
		brcmf_fw_crashed(&sdiod->func1->dev);
	}

	/* Dongle recomposed rx frames, accept them again */
	if (hmb_data & HMB_DATA_NAKHANDLED) {
		brcmf_dbg(SDIO, "Dongle reports NAK handled, expect rtx of %d\n",
			  bus->rx_seq);
		if (!bus->rxskip)
			brcmf_err("unexpected NAKHANDLED!\n");

		bus->rxskip = false;
		intstatus |= I_HMB_FRAME_IND;
	}

	/*
	 * DEVREADY does not occur with gSPI.
	 */
	if (hmb_data & (HMB_DATA_DEVREADY | HMB_DATA_FWREADY)) {
		bus->sdpcm_ver =
		    (hmb_data & HMB_DATA_VERSION_MASK) >>
		    HMB_DATA_VERSION_SHIFT;
		if (bus->sdpcm_ver != SDPCM_PROT_VERSION)
			brcmf_err("Version mismatch, dongle reports %d, "
				  "expecting %d\n",
				  bus->sdpcm_ver, SDPCM_PROT_VERSION);
		else
			brcmf_dbg(SDIO, "Dongle ready, protocol version %d\n",
				  bus->sdpcm_ver);

		/*
		 * Retrieve console state address now that firmware should have
		 * updated it.
		 */
		brcmf_sdio_get_console_addr(bus);
	}

	/*
	 * Flow Control has been moved into the RX headers and this out of band
	 * method isn't used any more.
	 * remaining backward compatible with older dongles.
	 */
	if (hmb_data & HMB_DATA_FC) {
		fcbits = (hmb_data & HMB_DATA_FCDATA_MASK) >>
							HMB_DATA_FCDATA_SHIFT;

		if (fcbits & ~bus->flowcontrol)
			bus->sdcnt.fc_xoff++;

		if (bus->flowcontrol & ~fcbits)
			bus->sdcnt.fc_xon++;

		bus->sdcnt.fc_rcvd++;
		bus->flowcontrol = fcbits;
	}

	/* Shouldn't be any others */
	if (hmb_data & ~(HMB_DATA_DEVREADY |
			 HMB_DATA_NAKHANDLED |
			 HMB_DATA_FC |
			 HMB_DATA_FWREADY |
			 HMB_DATA_FWHALT |
			 HMB_DATA_FCDATA_MASK | HMB_DATA_VERSION_MASK))
		brcmf_err("Unknown mailbox data content: 0x%02x\n",
			  hmb_data);

	return intstatus;
}