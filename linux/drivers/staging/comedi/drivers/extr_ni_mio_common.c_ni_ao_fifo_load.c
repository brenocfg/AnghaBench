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
struct ni_private {int /*<<< orphan*/  is_6711; scalar_t__ is_6xxx; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI611X_AO_FIFO_DATA_REG ; 
 int /*<<< orphan*/  NI_E_AO_FIFO_DATA_REG ; 
 int /*<<< orphan*/  comedi_buf_read_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writew (struct comedi_device*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_ao_fifo_load(struct comedi_device *dev,
			    struct comedi_subdevice *s, int n)
{
	struct ni_private *devpriv = dev->private;
	int i;
	unsigned short d;
	unsigned int packed_data;

	for (i = 0; i < n; i++) {
		comedi_buf_read_samples(s, &d, 1);

		if (devpriv->is_6xxx) {
			packed_data = d & 0xffff;
			/* 6711 only has 16 bit wide ao fifo */
			if (!devpriv->is_6711) {
				comedi_buf_read_samples(s, &d, 1);
				i++;
				packed_data |= (d << 16) & 0xffff0000;
			}
			ni_writel(dev, packed_data, NI611X_AO_FIFO_DATA_REG);
		} else {
			ni_writew(dev, d, NI_E_AO_FIFO_DATA_REG);
		}
	}
}