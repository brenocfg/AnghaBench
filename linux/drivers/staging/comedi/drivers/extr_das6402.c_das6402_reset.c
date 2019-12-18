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
struct das6402_private {int ao_range; } ;
struct comedi_device {scalar_t__ iobase; struct das6402_private* private; } ;

/* Variables and functions */
 int DAS6402_AI_MUX_HI (int /*<<< orphan*/ ) ; 
 int DAS6402_AI_MUX_LO (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS6402_AI_MUX_REG ; 
 scalar_t__ DAS6402_AO_DATA_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS6402_AO_LSB_REG (int /*<<< orphan*/ ) ; 
 int DAS6402_AO_RANGE (int,int) ; 
 scalar_t__ DAS6402_CTRL_REG ; 
 int DAS6402_CTRL_SOFT_TRIG ; 
 scalar_t__ DAS6402_DI_DO_REG ; 
 int DAS6402_MODE_ENHANCED ; 
 int DAS6402_MODE_POLLED ; 
 int DAS6402_MODE_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS6402_MODE_REG ; 
 int DAS6402_MODE_SE ; 
 int DAS6402_MODE_UNI ; 
 int /*<<< orphan*/  DAS6402_STATUS_W_10MHZ ; 
 scalar_t__ DAS6402_TRIG_REG ; 
 int /*<<< orphan*/  das6402_clear_all_interrupts (struct comedi_device*) ; 
 int /*<<< orphan*/  das6402_set_extended (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das6402_set_mode (struct comedi_device*,int) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void das6402_reset(struct comedi_device *dev)
{
	struct das6402_private *devpriv = dev->private;

	/* enable "Enhanced" mode */
	outb(DAS6402_MODE_ENHANCED, dev->iobase + DAS6402_MODE_REG);

	/* enable 10MHz pacer clock */
	das6402_set_extended(dev, DAS6402_STATUS_W_10MHZ);

	/* enable software conversion trigger */
	outb(DAS6402_CTRL_SOFT_TRIG, dev->iobase + DAS6402_CTRL_REG);

	/* default ADC to single-ended unipolar 10V inputs */
	das6402_set_mode(dev, DAS6402_MODE_RANGE(0) |
			      DAS6402_MODE_POLLED |
			      DAS6402_MODE_SE |
			      DAS6402_MODE_UNI);

	/* default mux for single channel conversion (channel 0) */
	outw(DAS6402_AI_MUX_HI(0) | DAS6402_AI_MUX_LO(0),
	     dev->iobase + DAS6402_AI_MUX_REG);

	/* set both DAC's for unipolar 5V output range */
	devpriv->ao_range = DAS6402_AO_RANGE(0, 2) | DAS6402_AO_RANGE(1, 2);
	outb(devpriv->ao_range, dev->iobase + DAS6402_TRIG_REG);

	/* set both DAC's to 0V */
	outw(0, dev->iobase + DAS6402_AO_DATA_REG(0));
	outw(0, dev->iobase + DAS6402_AO_DATA_REG(0));
	inw(dev->iobase + DAS6402_AO_LSB_REG(0));

	/* set all digital outputs low */
	outb(0, dev->iobase + DAS6402_DI_DO_REG);

	das6402_clear_all_interrupts(dev);
}