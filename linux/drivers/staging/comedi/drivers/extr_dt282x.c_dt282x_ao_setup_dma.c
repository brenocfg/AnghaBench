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
struct dt282x_private {struct comedi_isadma* dma; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_isadma_desc {int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  maxsize; } ;
struct comedi_isadma {struct comedi_isadma_desc* desc; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct dt282x_private* private; } ;

/* Variables and functions */
 unsigned int comedi_buf_read_samples (struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dt282x_prep_ao_dma (struct comedi_device*,int,unsigned int) ; 

__attribute__((used)) static unsigned int dt282x_ao_setup_dma(struct comedi_device *dev,
					struct comedi_subdevice *s,
					int cur_dma)
{
	struct dt282x_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[cur_dma];
	unsigned int nsamples = comedi_bytes_to_samples(s, desc->maxsize);
	unsigned int nbytes;

	nbytes = comedi_buf_read_samples(s, desc->virt_addr, nsamples);
	if (nbytes)
		dt282x_prep_ao_dma(dev, cur_dma, nbytes);
	else
		dev_err(dev->class_dev, "AO underrun\n");

	return nbytes;
}