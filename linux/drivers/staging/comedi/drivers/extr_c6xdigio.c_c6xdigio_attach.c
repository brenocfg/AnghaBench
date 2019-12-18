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
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int /*<<< orphan*/  insn_read; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; int /*<<< orphan*/  insn_write; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct comedi_devconfig {int /*<<< orphan*/ * options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_COUNTER ; 
 int /*<<< orphan*/  COMEDI_SUBD_PWM ; 
 int SDF_LSAMPL ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 int /*<<< orphan*/  c6xdigio_encoder_insn_read ; 
 int /*<<< orphan*/  c6xdigio_init (struct comedi_device*) ; 
 int /*<<< orphan*/  c6xdigio_pnp_driver ; 
 int /*<<< orphan*/  c6xdigio_pwm_insn_read ; 
 int /*<<< orphan*/  c6xdigio_pwm_insn_write ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_request_region (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pnp_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_unknown ; 

__attribute__((used)) static int c6xdigio_attach(struct comedi_device *dev,
			   struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	int ret;

	ret = comedi_request_region(dev, it->options[0], 0x03);
	if (ret)
		return ret;

	ret = comedi_alloc_subdevices(dev, 2);
	if (ret)
		return ret;

	/*  Make sure that PnP ports get activated */
	pnp_register_driver(&c6xdigio_pnp_driver);

	s = &dev->subdevices[0];
	/* pwm output subdevice */
	s->type		= COMEDI_SUBD_PWM;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 500;
	s->range_table	= &range_unknown;
	s->insn_write	= c6xdigio_pwm_insn_write;
	s->insn_read	= c6xdigio_pwm_insn_read;

	s = &dev->subdevices[1];
	/* encoder (counter) subdevice */
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_READABLE | SDF_LSAMPL;
	s->n_chan	= 2;
	s->maxdata	= 0xffffff;
	s->range_table	= &range_unknown;
	s->insn_read	= c6xdigio_encoder_insn_read;

	/*  I will call this init anyway but more than likely the DSP board */
	/*  will not be connected when device driver is loaded. */
	c6xdigio_init(dev);

	return 0;
}