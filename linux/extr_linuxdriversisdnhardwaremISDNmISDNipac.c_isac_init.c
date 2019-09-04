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
struct TYPE_2__ {int debug; int /*<<< orphan*/  timer; int /*<<< orphan*/  l1; } ;
struct isac_hw {int mocr; int type; int state; int adf2; int /*<<< orphan*/  name; TYPE_1__ dch; int /*<<< orphan*/ * mon_rx; int /*<<< orphan*/ * mon_tx; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int EINVAL ; 
 int IPACX__ON ; 
 int IPAC_TYPE_ISACX ; 
 int /*<<< orphan*/ * ISACVer ; 
 int /*<<< orphan*/  ISACX_CIR0 ; 
 int /*<<< orphan*/  ISACX_ID ; 
 int /*<<< orphan*/  ISACX_ISTA ; 
 int /*<<< orphan*/  ISACX_ISTAD ; 
 int /*<<< orphan*/  ISACX_MASK ; 
 int /*<<< orphan*/  ISACX_MASKD ; 
 int /*<<< orphan*/  ISACX_MODED ; 
 int /*<<< orphan*/  ISACX_STARD ; 
 int /*<<< orphan*/  ISACX_TR_CONF0 ; 
 int /*<<< orphan*/  ISACX_TR_CONF2 ; 
 int /*<<< orphan*/  ISAC_ADF1 ; 
 int /*<<< orphan*/  ISAC_ADF2 ; 
 int /*<<< orphan*/  ISAC_CIR0 ; 
 int /*<<< orphan*/  ISAC_CMD_RS ; 
 int /*<<< orphan*/  ISAC_EXIR ; 
 int /*<<< orphan*/  ISAC_ISTA ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  ISAC_MODE ; 
 int /*<<< orphan*/  ISAC_RBCH ; 
 int /*<<< orphan*/  ISAC_SPCR ; 
 int /*<<< orphan*/  ISAC_SQXR ; 
 int /*<<< orphan*/  ISAC_STAR ; 
 int /*<<< orphan*/  ISAC_STCR ; 
 int /*<<< orphan*/  ISAC_TIMR ; 
 int ReadISAC (struct isac_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteISAC (struct isac_hw*,int /*<<< orphan*/ ,int) ; 
 int create_l1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbusy_timer_handler ; 
 int /*<<< orphan*/  isac_l1cmd ; 
 int /*<<< orphan*/  isac_ph_state_change (struct isac_hw*) ; 
 int /*<<< orphan*/  isac_release (struct isac_hw*) ; 
 int /*<<< orphan*/  ph_command (struct isac_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isac_init(struct isac_hw *isac)
{
	u8 val;
	int err = 0;

	if (!isac->dch.l1) {
		err = create_l1(&isac->dch, isac_l1cmd);
		if (err)
			return err;
	}
	isac->mon_tx = NULL;
	isac->mon_rx = NULL;
	timer_setup(&isac->dch.timer, dbusy_timer_handler, 0);
	isac->mocr = 0xaa;
	if (isac->type & IPAC_TYPE_ISACX) {
		/* Disable all IRQ */
		WriteISAC(isac, ISACX_MASK, 0xff);
		val = ReadISAC(isac, ISACX_STARD);
		pr_debug("%s: ISACX STARD %x\n", isac->name, val);
		val = ReadISAC(isac, ISACX_ISTAD);
		pr_debug("%s: ISACX ISTAD %x\n", isac->name, val);
		val = ReadISAC(isac, ISACX_ISTA);
		pr_debug("%s: ISACX ISTA %x\n", isac->name, val);
		/* clear LDD */
		WriteISAC(isac, ISACX_TR_CONF0, 0x00);
		/* enable transmitter */
		WriteISAC(isac, ISACX_TR_CONF2, 0x00);
		/* transparent mode 0, RAC, stop/go */
		WriteISAC(isac, ISACX_MODED, 0xc9);
		/* all HDLC IRQ unmasked */
		val = ReadISAC(isac, ISACX_ID);
		if (isac->dch.debug & DEBUG_HW)
			pr_notice("%s: ISACX Design ID %x\n",
				  isac->name, val & 0x3f);
		val = ReadISAC(isac, ISACX_CIR0);
		pr_debug("%s: ISACX CIR0 %02X\n", isac->name, val);
		isac->state = val >> 4;
		isac_ph_state_change(isac);
		ph_command(isac, ISAC_CMD_RS);
		WriteISAC(isac, ISACX_MASK, IPACX__ON);
		WriteISAC(isac, ISACX_MASKD, 0x00);
	} else { /* old isac */
		WriteISAC(isac, ISAC_MASK, 0xff);
		val = ReadISAC(isac, ISAC_STAR);
		pr_debug("%s: ISAC STAR %x\n", isac->name, val);
		val = ReadISAC(isac, ISAC_MODE);
		pr_debug("%s: ISAC MODE %x\n", isac->name, val);
		val = ReadISAC(isac, ISAC_ADF2);
		pr_debug("%s: ISAC ADF2 %x\n", isac->name, val);
		val = ReadISAC(isac, ISAC_ISTA);
		pr_debug("%s: ISAC ISTA %x\n", isac->name, val);
		if (val & 0x01) {
			val = ReadISAC(isac, ISAC_EXIR);
			pr_debug("%s: ISAC EXIR %x\n", isac->name, val);
		}
		val = ReadISAC(isac, ISAC_RBCH);
		if (isac->dch.debug & DEBUG_HW)
			pr_notice("%s: ISAC version (%x): %s\n", isac->name,
				  val, ISACVer[(val >> 5) & 3]);
		isac->type |= ((val >> 5) & 3);
		if (!isac->adf2)
			isac->adf2 = 0x80;
		if (!(isac->adf2 & 0x80)) { /* only IOM 2 Mode */
			pr_info("%s: only support IOM2 mode but adf2=%02x\n",
				isac->name, isac->adf2);
			isac_release(isac);
			return -EINVAL;
		}
		WriteISAC(isac, ISAC_ADF2, isac->adf2);
		WriteISAC(isac, ISAC_SQXR, 0x2f);
		WriteISAC(isac, ISAC_SPCR, 0x00);
		WriteISAC(isac, ISAC_STCR, 0x70);
		WriteISAC(isac, ISAC_MODE, 0xc9);
		WriteISAC(isac, ISAC_TIMR, 0x00);
		WriteISAC(isac, ISAC_ADF1, 0x00);
		val = ReadISAC(isac, ISAC_CIR0);
		pr_debug("%s: ISAC CIR0 %x\n", isac->name, val);
		isac->state = (val >> 2) & 0xf;
		isac_ph_state_change(isac);
		ph_command(isac, ISAC_CMD_RS);
		WriteISAC(isac, ISAC_MASK, 0);
	}
	return err;
}