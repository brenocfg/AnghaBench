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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int S626_CRAMSK_INDXPOL_A ; 
 int S626_CRBMSK_INDXPOL_B ; 
 int S626_CRBMSK_INTCTRL ; 
 int /*<<< orphan*/  S626_LP_CRA (unsigned int) ; 
 int /*<<< orphan*/  S626_LP_CRB (unsigned int) ; 
 int s626_debi_read (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_debi_write (struct comedi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s626_pulse_index(struct comedi_device *dev,
			     unsigned int chan)
{
	if (chan < 3) {
		u16 cra;

		cra = s626_debi_read(dev, S626_LP_CRA(chan));

		/* Pulse index */
		s626_debi_write(dev, S626_LP_CRA(chan),
				(cra ^ S626_CRAMSK_INDXPOL_A));
		s626_debi_write(dev, S626_LP_CRA(chan), cra);
	} else {
		u16 crb;

		crb = s626_debi_read(dev, S626_LP_CRB(chan));
		crb &= ~S626_CRBMSK_INTCTRL;

		/* Pulse index */
		s626_debi_write(dev, S626_LP_CRB(chan),
				(crb ^ S626_CRBMSK_INDXPOL_B));
		s626_debi_write(dev, S626_LP_CRB(chan), crb);
	}
}