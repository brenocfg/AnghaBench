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
 int S626_CRBMSK_INTCTRL ; 
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
 int S626_SET_CRA_CLKMULT_A (unsigned int) ; 
 int S626_SET_CRA_CLKPOL_A (unsigned int) ; 
 int S626_SET_CRA_CNTSRC_A (unsigned int) ; 
 int S626_SET_CRA_INDXPOL_A (int /*<<< orphan*/ ) ; 
 int S626_SET_CRA_INDXSRC_A (scalar_t__) ; 
 int S626_SET_CRA_INTSRC_A (int /*<<< orphan*/ ) ; 
 int S626_SET_CRA_LOADSRC_A (int /*<<< orphan*/ ) ; 
 int S626_SET_CRB_CLKENAB_A (int /*<<< orphan*/ ) ; 
 int S626_SET_CRB_INTRESETCMD (int) ; 
 int S626_SET_CRB_INTRESET_A (int) ; 
 int /*<<< orphan*/  s626_debi_replace (struct comedi_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void s626_set_mode_a(struct comedi_device *dev,
			    unsigned int chan, u16 setup,
			    u16 disable_int_src)
{
	struct s626_private *devpriv = dev->private;
	u16 cra;
	u16 crb;
	unsigned int cntsrc, clkmult, clkpol;

	/* Initialize CRA and CRB images. */
	/* Preload trigger is passed through. */
	cra = S626_SET_CRA_LOADSRC_A(S626_GET_STD_LOADSRC(setup));
	/* IndexSrc is passed through. */
	cra |= S626_SET_CRA_INDXSRC_A(S626_GET_STD_INDXSRC(setup));

	/* Reset any pending CounterA event captures. */
	crb = S626_SET_CRB_INTRESETCMD(1) | S626_SET_CRB_INTRESET_A(1);
	/* Clock enable is passed through. */
	crb |= S626_SET_CRB_CLKENAB_A(S626_GET_STD_CLKENAB(setup));

	/* Force IntSrc to Disabled if disable_int_src is asserted. */
	if (!disable_int_src)
		cra |= S626_SET_CRA_INTSRC_A(S626_GET_STD_INTSRC(setup));

	/* Populate all mode-dependent attributes of CRA & CRB images. */
	clkpol = S626_GET_STD_CLKPOL(setup);
	switch (S626_GET_STD_ENCMODE(setup)) {
	case S626_ENCMODE_EXTENDER: /* Extender Mode: */
		/* Force to Timer mode (Extender valid only for B counters). */
		/* Fall through to case S626_ENCMODE_TIMER: */
	case S626_ENCMODE_TIMER:	/* Timer Mode: */
		/* CntSrcA<1> selects system clock */
		cntsrc = S626_CNTSRC_SYSCLK;
		/* Count direction (CntSrcA<0>) obtained from ClkPol. */
		cntsrc |= clkpol;
		/* ClkPolA behaves as always-on clock enable. */
		clkpol = 1;
		/* ClkMult must be 1x. */
		clkmult = S626_CLKMULT_1X;
		break;
	default:		/* Counter Mode: */
		/* Select ENC_C and ENC_D as clock/direction inputs. */
		cntsrc = S626_CNTSRC_ENCODER;
		/* Clock polarity is passed through. */
		/* Force multiplier to x1 if not legal, else pass through. */
		clkmult = S626_GET_STD_CLKMULT(setup);
		if (clkmult == S626_CLKMULT_SPECIAL)
			clkmult = S626_CLKMULT_1X;
		break;
	}
	cra |= S626_SET_CRA_CNTSRC_A(cntsrc) | S626_SET_CRA_CLKPOL_A(clkpol) |
	       S626_SET_CRA_CLKMULT_A(clkmult);

	/*
	 * Force positive index polarity if IndxSrc is software-driven only,
	 * otherwise pass it through.
	 */
	if (S626_GET_STD_INDXSRC(setup) != S626_INDXSRC_SOFT)
		cra |= S626_SET_CRA_INDXPOL_A(S626_GET_STD_INDXPOL(setup));

	/*
	 * If IntSrc has been forced to Disabled, update the MISC2 interrupt
	 * enable mask to indicate the counter interrupt is disabled.
	 */
	if (disable_int_src)
		devpriv->counter_int_enabs &= ~(S626_OVERMASK(chan) |
						S626_INDXMASK(chan));

	/*
	 * While retaining CounterB and LatchSrc configurations, program the
	 * new counter operating mode.
	 */
	s626_debi_replace(dev, S626_LP_CRA(chan),
			  S626_CRAMSK_INDXSRC_B | S626_CRAMSK_CNTSRC_B, cra);
	s626_debi_replace(dev, S626_LP_CRB(chan),
			  ~(S626_CRBMSK_INTCTRL | S626_CRBMSK_CLKENAB_A), crb);
}