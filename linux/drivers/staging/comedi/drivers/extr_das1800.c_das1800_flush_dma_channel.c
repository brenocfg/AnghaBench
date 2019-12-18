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
struct comedi_isadma_desc {unsigned int size; int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  chan; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,unsigned int) ; 
 unsigned int comedi_isadma_disable (int /*<<< orphan*/ ) ; 
 unsigned int comedi_nsamples_left (struct comedi_subdevice*,unsigned int) ; 

__attribute__((used)) static void das1800_flush_dma_channel(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_isadma_desc *desc)
{
	unsigned int residue = comedi_isadma_disable(desc->chan);
	unsigned int nbytes = desc->size - residue;
	unsigned int nsamples;

	/*  figure out how many points to read */
	nsamples = comedi_bytes_to_samples(s, nbytes);
	nsamples = comedi_nsamples_left(s, nsamples);

	comedi_buf_write_samples(s, desc->virt_addr, nsamples);
}