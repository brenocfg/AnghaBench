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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct w6692_hw {int imask; scalar_t__ subtype; int pctl; int xdata; int xaddr; int fmask; int /*<<< orphan*/  name; int /*<<< orphan*/ * bc; int /*<<< orphan*/  state; TYPE_1__ dch; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int /*<<< orphan*/  ISDN_P_NONE ; 
 int /*<<< orphan*/  ReadW6692 (struct w6692_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ W6692_USR ; 
 int /*<<< orphan*/  W_B_CMDR ; 
 int W_B_CMDR_RRST ; 
 int W_B_CMDR_XRST ; 
 int /*<<< orphan*/  W_B_EXIM ; 
 int /*<<< orphan*/  W_D_CMDR ; 
 int W_D_CMDR_RRST ; 
 int W_D_CMDR_XRST ; 
 int /*<<< orphan*/  W_D_CTL ; 
 int /*<<< orphan*/  W_D_EXIM ; 
 int /*<<< orphan*/  W_D_MODE ; 
 int W_D_MODE_RACT ; 
 int /*<<< orphan*/  W_D_SAM ; 
 int /*<<< orphan*/  W_D_TAM ; 
 int /*<<< orphan*/  W_L1CMD_ECK ; 
 int /*<<< orphan*/  W_L1CMD_RST ; 
 int /*<<< orphan*/  W_PCTL ; 
 int W_PCTL_OE0 ; 
 int W_PCTL_OE1 ; 
 int W_PCTL_OE2 ; 
 int W_PCTL_OE4 ; 
 int W_PCTL_OE5 ; 
 int /*<<< orphan*/  W_XADDR ; 
 int /*<<< orphan*/  W_XDATA ; 
 int /*<<< orphan*/  WriteW6692 (struct w6692_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteW6692B (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbusy_timer_handler ; 
 int debug ; 
 int /*<<< orphan*/  disable_hwirq (struct w6692_hw*) ; 
 int led ; 
 int /*<<< orphan*/  ph_command (struct w6692_hw*,int /*<<< orphan*/ ) ; 
 int pots ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w6692_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initW6692(struct w6692_hw *card)
{
	u8	val;

	timer_setup(&card->dch.timer, dbusy_timer_handler, 0);
	w6692_mode(&card->bc[0], ISDN_P_NONE);
	w6692_mode(&card->bc[1], ISDN_P_NONE);
	WriteW6692(card, W_D_CTL, 0x00);
	disable_hwirq(card);
	WriteW6692(card, W_D_SAM, 0xff);
	WriteW6692(card, W_D_TAM, 0xff);
	WriteW6692(card, W_D_MODE, W_D_MODE_RACT);
	card->state = W_L1CMD_RST;
	ph_command(card, W_L1CMD_RST);
	ph_command(card, W_L1CMD_ECK);
	/* enable all IRQ but extern */
	card->imask = 0x18;
	WriteW6692(card, W_D_EXIM, 0x00);
	WriteW6692B(&card->bc[0], W_B_EXIM, 0);
	WriteW6692B(&card->bc[1], W_B_EXIM, 0);
	/* Reset D-chan receiver and transmitter */
	WriteW6692(card, W_D_CMDR, W_D_CMDR_RRST | W_D_CMDR_XRST);
	/* Reset B-chan receiver and transmitter */
	WriteW6692B(&card->bc[0], W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_XRST);
	WriteW6692B(&card->bc[1], W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_XRST);
	/* enable peripheral */
	if (card->subtype == W6692_USR) {
		/* seems that USR implemented some power control features
		 * Pin 79 is connected to the oscilator circuit so we
		 * have to handle it here
		 */
		card->pctl = 0x80;
		card->xdata = 0;
		WriteW6692(card, W_PCTL, card->pctl);
		WriteW6692(card, W_XDATA, card->xdata);
	} else {
		card->pctl = W_PCTL_OE5 | W_PCTL_OE4 | W_PCTL_OE2 |
			W_PCTL_OE1 | W_PCTL_OE0;
		card->xaddr = 0x00;/* all sw off */
		if (card->fmask & pots)
			card->xdata |= 0x06;	/*  POWER UP/ LED OFF / ALAW */
		if (card->fmask & led)
			card->xdata |= 0x04;	/* LED OFF */
		if ((card->fmask & pots) || (card->fmask & led)) {
			WriteW6692(card, W_PCTL, card->pctl);
			WriteW6692(card, W_XADDR, card->xaddr);
			WriteW6692(card, W_XDATA, card->xdata);
			val = ReadW6692(card, W_XADDR);
			if (debug & DEBUG_HW)
				pr_notice("%s: W_XADDR=%02x\n",
					  card->name, val);
		}
	}
}