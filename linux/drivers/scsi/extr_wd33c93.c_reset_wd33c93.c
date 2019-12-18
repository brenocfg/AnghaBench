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
typedef  int /*<<< orphan*/  wd33c93_regs ;
typedef  int uchar ;
struct WD33C93_hostdata {int clock_freq; int default_sx_per; scalar_t__ chip; scalar_t__ fast; void* microcode; int /*<<< orphan*/  sx_table; int /*<<< orphan*/  regs; } ;
struct Scsi_Host {unsigned long base; int this_id; scalar_t__ hostdata; } ;

/* Variables and functions */
 int ASR_BSY ; 
 int ASR_INT ; 
 int CTRL_EDI ; 
 int CTRL_IDI ; 
 int CTRL_POLLED ; 
 scalar_t__ C_UNKNOWN_CHIP ; 
 scalar_t__ C_WD33C93 ; 
 scalar_t__ C_WD33C93A ; 
 scalar_t__ C_WD33C93B ; 
 int /*<<< orphan*/  DEFAULT_SX_OFF ; 
 int OWNID_EAF ; 
 int OWNID_RAF ; 
 int TIMEOUT_PERIOD_VALUE ; 
 int /*<<< orphan*/  WD_CDB_1 ; 
 int WD_CMD_RESET ; 
 int /*<<< orphan*/  WD_COMMAND ; 
 int /*<<< orphan*/  WD_CONTROL ; 
 int /*<<< orphan*/  WD_OWN_ID ; 
 int /*<<< orphan*/  WD_QUEUE_TAG ; 
 int /*<<< orphan*/  WD_SCSI_STATUS ; 
 int /*<<< orphan*/  WD_SYNCHRONOUS_TRANSFER ; 
 int /*<<< orphan*/  WD_TIMEOUT_PERIOD ; 
 int calc_sync_xfer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_aux_stat (int /*<<< orphan*/  const) ; 
 void* read_wd33c93 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_wd33c93 (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
reset_wd33c93(struct Scsi_Host *instance)
{
	struct WD33C93_hostdata *hostdata =
	    (struct WD33C93_hostdata *) instance->hostdata;
	const wd33c93_regs regs = hostdata->regs;
	uchar sr;

#ifdef CONFIG_SGI_IP22
	{
		int busycount = 0;
		extern void sgiwd93_reset(unsigned long);
		/* wait 'til the chip gets some time for us */
		while ((read_aux_stat(regs) & ASR_BSY) && busycount++ < 100)
			udelay (10);
	/*
 	 * there are scsi devices out there, which manage to lock up
	 * the wd33c93 in a busy condition. In this state it won't
	 * accept the reset command. The only way to solve this is to
 	 * give the chip a hardware reset (if possible). The code below
	 * does this for the SGI Indy, where this is possible
	 */
	/* still busy ? */
	if (read_aux_stat(regs) & ASR_BSY)
		sgiwd93_reset(instance->base); /* yeah, give it the hard one */
	}
#endif

	write_wd33c93(regs, WD_OWN_ID, OWNID_EAF | OWNID_RAF |
		      instance->this_id | hostdata->clock_freq);
	write_wd33c93(regs, WD_CONTROL, CTRL_IDI | CTRL_EDI | CTRL_POLLED);
	write_wd33c93(regs, WD_SYNCHRONOUS_TRANSFER,
		      calc_sync_xfer(hostdata->default_sx_per / 4,
				     DEFAULT_SX_OFF, 0, hostdata->sx_table));
	write_wd33c93(regs, WD_COMMAND, WD_CMD_RESET);


#ifdef CONFIG_MVME147_SCSI
	udelay(25);		/* The old wd33c93 on MVME147 needs this, at least */
#endif

	while (!(read_aux_stat(regs) & ASR_INT))
		;
	sr = read_wd33c93(regs, WD_SCSI_STATUS);

	hostdata->microcode = read_wd33c93(regs, WD_CDB_1);
	if (sr == 0x00)
		hostdata->chip = C_WD33C93;
	else if (sr == 0x01) {
		write_wd33c93(regs, WD_QUEUE_TAG, 0xa5);	/* any random number */
		sr = read_wd33c93(regs, WD_QUEUE_TAG);
		if (sr == 0xa5) {
			hostdata->chip = C_WD33C93B;
			write_wd33c93(regs, WD_QUEUE_TAG, 0);
		} else
			hostdata->chip = C_WD33C93A;
	} else
		hostdata->chip = C_UNKNOWN_CHIP;

	if (hostdata->chip != C_WD33C93B)	/* Fast SCSI unavailable */
		hostdata->fast = 0;

	write_wd33c93(regs, WD_TIMEOUT_PERIOD, TIMEOUT_PERIOD_VALUE);
	write_wd33c93(regs, WD_CONTROL, CTRL_IDI | CTRL_EDI | CTRL_POLLED);
}