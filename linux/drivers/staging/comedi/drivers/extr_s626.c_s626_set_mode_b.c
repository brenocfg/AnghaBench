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
typedef  int u16 ;
struct s626_private {int counter_int_enabs; } ;
struct comedi_device {struct s626_private* private; } ;

/* Variables and functions */
 unsigned int S626_CLKMULT_1X ; 
 unsigned int S626_CLKMULT_SPECIAL ; 
 unsigned int S626_CNTSRC_ENCODER ; 
 unsigned int S626_CNTSRC_SYSCLK ; 
 int S626_CRAMSK_CNTSRC_B ; 
 int S626_CRAMSK_INDXSRC_B ; 
 int S626_CRBMSK_CLKENAB_A ; 
 int S626_CRBMSK_LATCHSRC ; 
#define  S626_ENCMODE_EXTENDER 129 
#define  S626_ENCMODE_TIMER 128 
 int /*<<< orphan*/  S626_GET_STD_CLKENAB (int) ; 
 unsigned int S626_GET_STD_CLKMULT (int) ; 
 unsigned int S626_GET_STD_CLKPOL (int) ; 
 int S626_GET_STD_ENCMODE (int) ; 
 int /*<<< orphan*/  S626_GET_STD_INDXPOL (int) ; 
 scalar_t__ S626_GET_STD_INDXSRC (int) ; 
 int /*<<< orphan*/  S626_GET_STD_INTSRC (int) ; 
 int /*<<< orphan*/  S626_GET_STD_LOADSRC (int) ; 
 int S626_INDXMASK (unsigned int) ; 
 scalar_t__ S626_INDXSRC_SOFT ; 
 int /*<<< orphan*/  S626_LP_CRA (unsigned int) ; 
 int /*<<< orphan*/  S626_LP_CRB (unsigned int) ; 
 int S626_OVERMASK (unsigned int) ; 
 int S626_SET_CRA_CNTSRC_B (unsigned int) ; 
 int S626_SET_CRA_INDXSRC_B (scalar_t__) ; 
 int S626_SET_CRB_CLKENAB_B (int /*<<< orphan*/ ) ; 
 int S626_SET_CRB_CLKMULT_B (unsigned int) ; 
 int S626_SET_CRB_CLKPOL_B (unsigned int) ; 
 int S626_SET_CRB_INDXPOL_B (int /*<<< orphan*/ ) ; 
 int S626_SET_CRB_INTRESETCMD (int) ; 
 int S626_SET_CRB_INTRESET_B (int) ; 
 int S626_SET_CRB_INTSRC_B (int /*<<< orphan*/ ) ; 
 int S626_SET_CRB_LOADSRC_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_debi_replace (struct comedi_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void s626_set_mode_b(struct comedi_device *dev,
			    unsigned int chan, u16 setup,
			    u16 disable_int_src)
{
	struct s626_private *devpriv = dev->private;
	u16 cra;
	u16 crb;
	unsigned int cntsrc, clkmult, clkpol;

	/* Initialize CRA and CRB images. */
	/* IndexSrc is passed through. */
	cra = S626_SET_CRA_INDXSRC_B(S626_GET_STD_INDXSRC(setup));

	/* Reset event captures and disable interrupts. */
	crb = S626_SET_CRB_INTRESETCMD(1) | S626_SET_CRB_INTRESET_B(1);
	/* Clock enable is passed through. */
	crb |= S626_SET_CRB_CLKENAB_B(S626_GET_STD_CLKENAB(setup));
	/* Preload trigger source is passed through. */
	crb |= S626_SET_CRB_LOADSRC_B(S626_GET_STD_LOADSRC(setup));

	/* Force IntSrc to Disabled if disable_int_src is asserted. */
	if (!disable_int_src)
		crb |= S626_SET_CRB_INTSRC_B(S626_GET_STD_INTSRC(setup));

	/* Populate all mode-dependent attributes of CRA & CRB images. */
	clkpol = S626_GET_STD_CLKPOL(setup);
	switch (S626_GET_STD_ENCMODE(setup)) {
	case S626_ENCMODE_TIMER:	/* Timer Mode: */
		/* CntSrcB<1> selects system clock */
		cntsrc = S626_CNTSRC_SYSCLK;
		/* with direction (CntSrcB<0>) obtained from ClkPol. */
		cntsrc |= clkpol;
		/* ClkPolB behaves as always-on clock enable. */
		clkpol = 1;
		/* ClkMultB must be 1x. */
		clkmult = S626_CLKMULT_1X;
		break;
	case S626_ENCMODE_EXTENDER:	/* Extender Mode: */
		/* CntSrcB source is OverflowA (same as "timer") */
		cntsrc = S626_CNTSRC_SYSCLK;
		/* with direction obtained from ClkPol. */
		cntsrc |= clkpol;
		/* ClkPolB controls IndexB -- always set to active. */
		clkpol = 1;
		/* ClkMultB selects OverflowA as the clock source. */
		clkmult = S626_CLKMULT_SPECIAL;
		break;
	default:		/* Counter Mode: */
		/* Select ENC_C and ENC_D as clock/direction inputs. */
		cntsrc = S626_CNTSRC_ENCODER;
		/* ClkPol is passed through. */
		/* Force ClkMult to x1 if not legal, otherwise pass through. */
		clkmult = S626_GET_STD_CLKMULT(setup);
		if (clkmult == S626_CLKMULT_SPECIAL)
			clkmult = S626_CLKMULT_1X;
		break;
	}
	cra |= S626_SET_CRA_CNTSRC_B(cntsrc);
	crb |= S626_SET_CRB_CLKPOL_B(clkpol) | S626_SET_CRB_CLKMULT_B(clkmult);

	/*
	 * Force positive index polarity if IndxSrc is software-driven only,
	 * otherwise pass it through.
	 */
	if (S626_GET_STD_INDXSRC(setup) != S626_INDXSRC_SOFT)
		crb |= S626_SET_CRB_INDXPOL_B(S626_GET_STD_INDXPOL(setup));

	/*
	 * If IntSrc has been forced to Disabled, update the MISC2 interrupt
	 * enable mask to indicate the counter interrupt is disabled.
	 */
	if (disable_int_src)
		devpriv->counter_int_enabs &= ~(S626_OVERMASK(chan) |
						S626_INDXMASK(chan));

	/*
	 * While retaining CounterA and LatchSrc configurations, program the
	 * new counter operating mode.
	 */
	s626_debi_replace(dev, S626_LP_CRA(chan),
			  ~(S626_CRAMSK_INDXSRC_B | S626_CRAMSK_CNTSRC_B), cra);
	s626_debi_replace(dev, S626_LP_CRB(chan),
			  S626_CRBMSK_CLKENAB_A | S626_CRBMSK_LATCHSRC, crb);
}