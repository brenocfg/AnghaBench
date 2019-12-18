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
struct comedi_subdevice {int /*<<< orphan*/  type; scalar_t__ private; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int COMEDI_INPUT ; 
 unsigned int COMEDI_OUTPUT ; 
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_INPUT 131 
#define  INSN_CONFIG_DIO_OUTPUT 130 
#define  INSN_CONFIG_DIO_QUERY 129 
#define  INSN_CONFIG_FILTER 128 
 unsigned int NI_65XX_CHAN_TO_MASK (unsigned int) ; 
 unsigned long NI_65XX_CHAN_TO_PORT (unsigned int) ; 
 scalar_t__ NI_65XX_FILTER_ENA (unsigned int) ; 
 scalar_t__ NI_65XX_FILTER_REG ; 
 unsigned int NI_65XX_IO_SEL_INPUT ; 
 unsigned int NI_65XX_IO_SEL_OUTPUT ; 
 scalar_t__ NI_65XX_IO_SEL_REG (unsigned int) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int ni_65xx_dio_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned long base_port = (unsigned long)s->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int chan_mask = NI_65XX_CHAN_TO_MASK(chan);
	unsigned int port = base_port + NI_65XX_CHAN_TO_PORT(chan);
	unsigned int interval;
	unsigned int val;

	switch (data[0]) {
	case INSN_CONFIG_FILTER:
		/*
		 * The deglitch filter interval is specified in nanoseconds.
		 * The hardware supports intervals in 200ns increments. Round
		 * the user values up and return the actual interval.
		 */
		interval = (data[1] + 100) / 200;
		if (interval > 0xfffff)
			interval = 0xfffff;
		data[1] = interval * 200;

		/*
		 * Enable/disable the channel for deglitch filtering. Note
		 * that the filter interval is never set to '0'. This is done
		 * because other channels might still be enabled for filtering.
		 */
		val = readb(dev->mmio + NI_65XX_FILTER_ENA(port));
		if (interval) {
			writel(interval, dev->mmio + NI_65XX_FILTER_REG);
			val |= chan_mask;
		} else {
			val &= ~chan_mask;
		}
		writeb(val, dev->mmio + NI_65XX_FILTER_ENA(port));
		break;

	case INSN_CONFIG_DIO_OUTPUT:
		if (s->type != COMEDI_SUBD_DIO)
			return -EINVAL;
		writeb(NI_65XX_IO_SEL_OUTPUT,
		       dev->mmio + NI_65XX_IO_SEL_REG(port));
		break;

	case INSN_CONFIG_DIO_INPUT:
		if (s->type != COMEDI_SUBD_DIO)
			return -EINVAL;
		writeb(NI_65XX_IO_SEL_INPUT,
		       dev->mmio + NI_65XX_IO_SEL_REG(port));
		break;

	case INSN_CONFIG_DIO_QUERY:
		if (s->type != COMEDI_SUBD_DIO)
			return -EINVAL;
		val = readb(dev->mmio + NI_65XX_IO_SEL_REG(port));
		data[1] = (val == NI_65XX_IO_SEL_INPUT) ? COMEDI_INPUT
							: COMEDI_OUTPUT;
		break;

	default:
		return -EINVAL;
	}

	return insn->n;
}