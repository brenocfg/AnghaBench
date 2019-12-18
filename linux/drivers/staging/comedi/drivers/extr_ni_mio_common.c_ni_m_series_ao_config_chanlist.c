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
struct ni_private {unsigned int* ao_conf; } ;
struct comedi_subdevice {int n_chan; TYPE_1__* range_table; } ;
struct comedi_krange {int max; int min; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;
struct TYPE_2__ {struct comedi_krange* range; } ;

/* Variables and functions */
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 unsigned int NI_M_AO_CFG_BANK_OFFSET_0V ; 
 unsigned int NI_M_AO_CFG_BANK_OFFSET_5V ; 
 unsigned int NI_M_AO_CFG_BANK_REF_INT_10V ; 
 unsigned int NI_M_AO_CFG_BANK_REF_INT_5V ; 
 int /*<<< orphan*/  NI_M_AO_CFG_BANK_REG (unsigned int) ; 
 unsigned int NI_M_AO_CFG_BANK_UPDATE_TIMED ; 
 int /*<<< orphan*/  NI_M_AO_REF_ATTENUATION_REG (unsigned int) ; 
 int NI_M_AO_REF_ATTENUATION_X5 ; 
 int /*<<< orphan*/  NI_M_AO_WAVEFORM_ORDER_REG (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ni_writeb (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_m_series_ao_config_chanlist(struct comedi_device *dev,
					  struct comedi_subdevice *s,
					  unsigned int chanspec[],
					  unsigned int n_chans, int timed)
{
	struct ni_private *devpriv = dev->private;
	unsigned int range;
	unsigned int chan;
	unsigned int conf;
	int i;
	int invert = 0;

	if (timed) {
		for (i = 0; i < s->n_chan; ++i) {
			devpriv->ao_conf[i] &= ~NI_M_AO_CFG_BANK_UPDATE_TIMED;
			ni_writeb(dev, devpriv->ao_conf[i],
				  NI_M_AO_CFG_BANK_REG(i));
			ni_writeb(dev, 0xf, NI_M_AO_WAVEFORM_ORDER_REG(i));
		}
	}
	for (i = 0; i < n_chans; i++) {
		const struct comedi_krange *krange;

		chan = CR_CHAN(chanspec[i]);
		range = CR_RANGE(chanspec[i]);
		krange = s->range_table->range + range;
		invert = 0;
		conf = 0;
		switch (krange->max - krange->min) {
		case 20000000:
			conf |= NI_M_AO_CFG_BANK_REF_INT_10V;
			ni_writeb(dev, 0, NI_M_AO_REF_ATTENUATION_REG(chan));
			break;
		case 10000000:
			conf |= NI_M_AO_CFG_BANK_REF_INT_5V;
			ni_writeb(dev, 0, NI_M_AO_REF_ATTENUATION_REG(chan));
			break;
		case 4000000:
			conf |= NI_M_AO_CFG_BANK_REF_INT_10V;
			ni_writeb(dev, NI_M_AO_REF_ATTENUATION_X5,
				  NI_M_AO_REF_ATTENUATION_REG(chan));
			break;
		case 2000000:
			conf |= NI_M_AO_CFG_BANK_REF_INT_5V;
			ni_writeb(dev, NI_M_AO_REF_ATTENUATION_X5,
				  NI_M_AO_REF_ATTENUATION_REG(chan));
			break;
		default:
			dev_err(dev->class_dev,
				"bug! unhandled ao reference voltage\n");
			break;
		}
		switch (krange->max + krange->min) {
		case 0:
			conf |= NI_M_AO_CFG_BANK_OFFSET_0V;
			break;
		case 10000000:
			conf |= NI_M_AO_CFG_BANK_OFFSET_5V;
			break;
		default:
			dev_err(dev->class_dev,
				"bug! unhandled ao offset voltage\n");
			break;
		}
		if (timed)
			conf |= NI_M_AO_CFG_BANK_UPDATE_TIMED;
		ni_writeb(dev, conf, NI_M_AO_CFG_BANK_REG(chan));
		devpriv->ao_conf[chan] = conf;
		ni_writeb(dev, i, NI_M_AO_WAVEFORM_ORDER_REG(chan));
	}
	return invert;
}