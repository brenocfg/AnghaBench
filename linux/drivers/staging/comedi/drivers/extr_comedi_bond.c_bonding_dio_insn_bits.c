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
struct comedi_bond_private {unsigned int nchans; struct bonded_device** devs; } ;
struct bonded_device {unsigned int nchans; int /*<<< orphan*/  subdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int comedi_dio_bitfield2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*,unsigned int) ; 

__attribute__((used)) static int bonding_dio_insn_bits(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	struct comedi_bond_private *devpriv = dev->private;
	unsigned int n_left, n_done, base_chan;
	unsigned int write_mask, data_bits;
	struct bonded_device **devs;

	write_mask = data[0];
	data_bits = data[1];
	base_chan = CR_CHAN(insn->chanspec);
	/* do a maximum of 32 channels, starting from base_chan. */
	n_left = devpriv->nchans - base_chan;
	if (n_left > 32)
		n_left = 32;

	n_done = 0;
	devs = devpriv->devs;
	do {
		struct bonded_device *bdev = *devs++;

		if (base_chan < bdev->nchans) {
			/* base channel falls within bonded device */
			unsigned int b_chans, b_mask, b_write_mask, b_data_bits;
			int ret;

			/*
			 * Get num channels to do for bonded device and set
			 * up mask and data bits for bonded device.
			 */
			b_chans = bdev->nchans - base_chan;
			if (b_chans > n_left)
				b_chans = n_left;
			b_mask = (b_chans < 32) ? ((1 << b_chans) - 1)
						: 0xffffffff;
			b_write_mask = (write_mask >> n_done) & b_mask;
			b_data_bits = (data_bits >> n_done) & b_mask;
			/* Read/Write the new digital lines. */
			ret = comedi_dio_bitfield2(bdev->dev, bdev->subdev,
						   b_write_mask, &b_data_bits,
						   base_chan);
			if (ret < 0)
				return ret;
			/* Place read bits into data[1]. */
			data[1] &= ~(b_mask << n_done);
			data[1] |= (b_data_bits & b_mask) << n_done;
			/*
			 * Set up for following bonded device (if still have
			 * channels to read/write).
			 */
			base_chan = 0;
			n_done += b_chans;
			n_left -= b_chans;
		} else {
			/* Skip bonded devices before base channel. */
			base_chan -= bdev->nchans;
		}
	} while (n_left);

	return insn->n;
}