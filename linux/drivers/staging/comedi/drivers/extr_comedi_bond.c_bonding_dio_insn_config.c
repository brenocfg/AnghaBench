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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct comedi_bond_private* private; } ;
struct comedi_bond_private {struct bonded_device** devs; } ;
struct bonded_device {unsigned int nchans; int /*<<< orphan*/  subdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_INPUT 130 
#define  INSN_CONFIG_DIO_OUTPUT 129 
#define  INSN_CONFIG_DIO_QUERY 128 
 int comedi_dio_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int comedi_dio_get_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int bonding_dio_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn, unsigned int *data)
{
	struct comedi_bond_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	int ret;
	struct bonded_device *bdev;
	struct bonded_device **devs;

	/*
	 * Locate bonded subdevice and adjust channel.
	 */
	devs = devpriv->devs;
	for (bdev = *devs++; chan >= bdev->nchans; bdev = *devs++)
		chan -= bdev->nchans;

	/*
	 * The input or output configuration of each digital line is
	 * configured by a special insn_config instruction.  chanspec
	 * contains the channel to be changed, and data[0] contains the
	 * configuration instruction INSN_CONFIG_DIO_OUTPUT,
	 * INSN_CONFIG_DIO_INPUT or INSN_CONFIG_DIO_QUERY.
	 *
	 * Note that INSN_CONFIG_DIO_OUTPUT == COMEDI_OUTPUT,
	 * and INSN_CONFIG_DIO_INPUT == COMEDI_INPUT.  This is deliberate ;)
	 */
	switch (data[0]) {
	case INSN_CONFIG_DIO_OUTPUT:
	case INSN_CONFIG_DIO_INPUT:
		ret = comedi_dio_config(bdev->dev, bdev->subdev, chan, data[0]);
		break;
	case INSN_CONFIG_DIO_QUERY:
		ret = comedi_dio_get_config(bdev->dev, bdev->subdev, chan,
					    &data[1]);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	if (ret >= 0)
		ret = insn->n;
	return ret;
}