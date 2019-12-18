#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pcf50633 {int onkey1s_held; int* mask_regs; int* resume_reason; TYPE_1__* pdata; scalar_t__ is_suspended; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int* resumers; int /*<<< orphan*/  (* force_shutdown ) (struct pcf50633*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PCF50633_INT1_ADPINS ; 
 int PCF50633_INT1_ADPREM ; 
 int PCF50633_INT1_SECOND ; 
 int PCF50633_INT1_USBINS ; 
 int PCF50633_INT1_USBREM ; 
 int PCF50633_INT2_ONKEYF ; 
 int PCF50633_INT2_ONKEYR ; 
 int PCF50633_INT3_ONKEY1S ; 
 scalar_t__ PCF50633_ONKEY1S_TIMEOUT ; 
 int /*<<< orphan*/  PCF50633_REG_INT1 ; 
 int /*<<< orphan*/  PCF50633_REG_INT1M ; 
 int /*<<< orphan*/  PCF50633_REG_INT2M ; 
 int /*<<< orphan*/  PCF50633_REG_MBCS2 ; 
 int /*<<< orphan*/  PCF50633_REG_OOCSHDWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pcf50633_irq_call_handler (struct pcf50633*,int) ; 
 int pcf50633_read_block (struct pcf50633*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pcf50633_reg_clear_bits (struct pcf50633*,int /*<<< orphan*/ ,int) ; 
 int pcf50633_reg_read (struct pcf50633*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf50633_reg_set_bit_mask (struct pcf50633*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pcf50633_reg_write (struct pcf50633*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct pcf50633*) ; 

__attribute__((used)) static irqreturn_t pcf50633_irq(int irq, void *data)
{
	struct pcf50633 *pcf = data;
	int ret, i, j;
	u8 pcf_int[5], chgstat;

	/* Read the 5 INT regs in one transaction */
	ret = pcf50633_read_block(pcf, PCF50633_REG_INT1,
						ARRAY_SIZE(pcf_int), pcf_int);
	if (ret != ARRAY_SIZE(pcf_int)) {
		dev_err(pcf->dev, "Error reading INT registers\n");

		/*
		 * If this doesn't ACK the interrupt to the chip, we'll be
		 * called once again as we're level triggered.
		 */
		goto out;
	}

	/* defeat 8s death from lowsys on A5 */
	pcf50633_reg_write(pcf, PCF50633_REG_OOCSHDWN,  0x04);

	/* We immediately read the usb and adapter status. We thus make sure
	 * only of USBINS/USBREM IRQ handlers are called */
	if (pcf_int[0] & (PCF50633_INT1_USBINS | PCF50633_INT1_USBREM)) {
		chgstat = pcf50633_reg_read(pcf, PCF50633_REG_MBCS2);
		if (chgstat & (0x3 << 4))
			pcf_int[0] &= ~PCF50633_INT1_USBREM;
		else
			pcf_int[0] &= ~PCF50633_INT1_USBINS;
	}

	/* Make sure only one of ADPINS or ADPREM is set */
	if (pcf_int[0] & (PCF50633_INT1_ADPINS | PCF50633_INT1_ADPREM)) {
		chgstat = pcf50633_reg_read(pcf, PCF50633_REG_MBCS2);
		if (chgstat & (0x3 << 4))
			pcf_int[0] &= ~PCF50633_INT1_ADPREM;
		else
			pcf_int[0] &= ~PCF50633_INT1_ADPINS;
	}

	dev_dbg(pcf->dev, "INT1=0x%02x INT2=0x%02x INT3=0x%02x "
			"INT4=0x%02x INT5=0x%02x\n", pcf_int[0],
			pcf_int[1], pcf_int[2], pcf_int[3], pcf_int[4]);

	/* Some revisions of the chip don't have a 8s standby mode on
	 * ONKEY1S press. We try to manually do it in such cases. */
	if ((pcf_int[0] & PCF50633_INT1_SECOND) && pcf->onkey1s_held) {
		dev_info(pcf->dev, "ONKEY1S held for %d secs\n",
							pcf->onkey1s_held);
		if (pcf->onkey1s_held++ == PCF50633_ONKEY1S_TIMEOUT)
			if (pcf->pdata->force_shutdown)
				pcf->pdata->force_shutdown(pcf);
	}

	if (pcf_int[2] & PCF50633_INT3_ONKEY1S) {
		dev_info(pcf->dev, "ONKEY1S held\n");
		pcf->onkey1s_held = 1 ;

		/* Unmask IRQ_SECOND */
		pcf50633_reg_clear_bits(pcf, PCF50633_REG_INT1M,
						PCF50633_INT1_SECOND);

		/* Unmask IRQ_ONKEYR */
		pcf50633_reg_clear_bits(pcf, PCF50633_REG_INT2M,
						PCF50633_INT2_ONKEYR);
	}

	if ((pcf_int[1] & PCF50633_INT2_ONKEYR) && pcf->onkey1s_held) {
		pcf->onkey1s_held = 0;

		/* Mask SECOND and ONKEYR interrupts */
		if (pcf->mask_regs[0] & PCF50633_INT1_SECOND)
			pcf50633_reg_set_bit_mask(pcf,
					PCF50633_REG_INT1M,
					PCF50633_INT1_SECOND,
					PCF50633_INT1_SECOND);

		if (pcf->mask_regs[1] & PCF50633_INT2_ONKEYR)
			pcf50633_reg_set_bit_mask(pcf,
					PCF50633_REG_INT2M,
					PCF50633_INT2_ONKEYR,
					PCF50633_INT2_ONKEYR);
	}

	/* Have we just resumed ? */
	if (pcf->is_suspended) {
		pcf->is_suspended = 0;

		/* Set the resume reason filtering out non resumers */
		for (i = 0; i < ARRAY_SIZE(pcf_int); i++)
			pcf->resume_reason[i] = pcf_int[i] &
						pcf->pdata->resumers[i];

		/* Make sure we don't pass on any ONKEY events to
		 * userspace now */
		pcf_int[1] &= ~(PCF50633_INT2_ONKEYR | PCF50633_INT2_ONKEYF);
	}

	for (i = 0; i < ARRAY_SIZE(pcf_int); i++) {
		/* Unset masked interrupts */
		pcf_int[i] &= ~pcf->mask_regs[i];

		for (j = 0; j < 8 ; j++)
			if (pcf_int[i] & (1 << j))
				pcf50633_irq_call_handler(pcf, (i * 8) + j);
	}

out:
	return IRQ_HANDLED;
}