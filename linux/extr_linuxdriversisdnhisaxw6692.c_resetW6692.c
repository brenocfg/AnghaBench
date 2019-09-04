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
struct IsdnCardState {scalar_t__ subtyp; int /*<<< orphan*/  (* writeW6692 ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ W6692_USR ; 
 int /*<<< orphan*/  W_D_CTL ; 
 int W_D_CTL_SRST ; 
 int /*<<< orphan*/  W_D_EXIM ; 
 int /*<<< orphan*/  W_D_MODE ; 
 int W_D_MODE_RACT ; 
 int /*<<< orphan*/  W_D_SAM ; 
 int /*<<< orphan*/  W_D_TAM ; 
 int /*<<< orphan*/  W_IMASK ; 
 int /*<<< orphan*/  W_PCTL ; 
 int /*<<< orphan*/  W_XDATA ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void resetW6692(struct IsdnCardState *cs)
{
	cs->writeW6692(cs, W_D_CTL, W_D_CTL_SRST);
	mdelay(10);
	cs->writeW6692(cs, W_D_CTL, 0x00);
	mdelay(10);
	cs->writeW6692(cs, W_IMASK, 0xff);
	cs->writeW6692(cs, W_D_SAM, 0xff);
	cs->writeW6692(cs, W_D_TAM, 0xff);
	cs->writeW6692(cs, W_D_EXIM, 0x00);
	cs->writeW6692(cs, W_D_MODE, W_D_MODE_RACT);
	cs->writeW6692(cs, W_IMASK, 0x18);
	if (cs->subtyp == W6692_USR) {
		/* seems that USR implemented some power control features
		 * Pin 79 is connected to the oscilator circuit so we
		 * have to handle it here
		 */
		cs->writeW6692(cs, W_PCTL, 0x80);
		cs->writeW6692(cs, W_XDATA, 0x00);
	}
}