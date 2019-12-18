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
struct pcidas64_private {scalar_t__ plx9080_iobase; } ;
struct comedi_device {struct pcidas64_private* private; } ;

/* Variables and functions */
 scalar_t__ PLX_REG_DMADPR0 ; 
 scalar_t__ PLX_REG_DMADPR1 ; 
 scalar_t__ PLX_REG_DMALADR0 ; 
 scalar_t__ PLX_REG_DMALADR1 ; 
 scalar_t__ PLX_REG_DMAPADR0 ; 
 scalar_t__ PLX_REG_DMAPADR1 ; 
 scalar_t__ PLX_REG_DMASIZ0 ; 
 scalar_t__ PLX_REG_DMASIZ1 ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void load_first_dma_descriptor(struct comedi_device *dev,
					     unsigned int dma_channel,
					     unsigned int descriptor_bits)
{
	struct pcidas64_private *devpriv = dev->private;

	/*
	 * The transfer size, pci address, and local address registers
	 * are supposedly unused during chained dma,
	 * but I have found that left over values from last operation
	 * occasionally cause problems with transfer of first dma
	 * block.  Initializing them to zero seems to fix the problem.
	 */
	if (dma_channel) {
		writel(0, devpriv->plx9080_iobase + PLX_REG_DMASIZ1);
		writel(0, devpriv->plx9080_iobase + PLX_REG_DMAPADR1);
		writel(0, devpriv->plx9080_iobase + PLX_REG_DMALADR1);
		writel(descriptor_bits,
		       devpriv->plx9080_iobase + PLX_REG_DMADPR1);
	} else {
		writel(0, devpriv->plx9080_iobase + PLX_REG_DMASIZ0);
		writel(0, devpriv->plx9080_iobase + PLX_REG_DMAPADR0);
		writel(0, devpriv->plx9080_iobase + PLX_REG_DMALADR0);
		writel(descriptor_bits,
		       devpriv->plx9080_iobase + PLX_REG_DMADPR0);
	}
}