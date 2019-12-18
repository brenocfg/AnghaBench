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
struct ni_private {unsigned int* ao_conf; } ;
struct comedi_subdevice {int maxdata; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 scalar_t__ AREF_OTHER ; 
 scalar_t__ CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_DEGLITCH ; 
 unsigned int CR_RANGE (unsigned int) ; 
 unsigned int NI_E_AO_CFG_BIP ; 
 int /*<<< orphan*/  NI_E_AO_CFG_REG ; 
 unsigned int NI_E_AO_DACSEL (unsigned int) ; 
 unsigned int NI_E_AO_DEGLITCH ; 
 unsigned int NI_E_AO_EXT_REF ; 
 unsigned int NI_E_AO_GROUND_REF ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 scalar_t__ comedi_range_is_external (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  ni_writew (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_old_ao_config_chanlist(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     unsigned int chanspec[],
				     unsigned int n_chans)
{
	struct ni_private *devpriv = dev->private;
	unsigned int range;
	unsigned int chan;
	unsigned int conf;
	int i;
	int invert = 0;

	for (i = 0; i < n_chans; i++) {
		chan = CR_CHAN(chanspec[i]);
		range = CR_RANGE(chanspec[i]);
		conf = NI_E_AO_DACSEL(chan);

		if (comedi_range_is_bipolar(s, range)) {
			conf |= NI_E_AO_CFG_BIP;
			invert = (s->maxdata + 1) >> 1;
		} else {
			invert = 0;
		}
		if (comedi_range_is_external(s, range))
			conf |= NI_E_AO_EXT_REF;

		/* not all boards can deglitch, but this shouldn't hurt */
		if (chanspec[i] & CR_DEGLITCH)
			conf |= NI_E_AO_DEGLITCH;

		/* analog reference */
		/* AREF_OTHER connects AO ground to AI ground, i think */
		if (CR_AREF(chanspec[i]) == AREF_OTHER)
			conf |= NI_E_AO_GROUND_REF;

		ni_writew(dev, conf, NI_E_AO_CFG_REG);
		devpriv->ao_conf[chan] = conf;
	}
	return invert;
}