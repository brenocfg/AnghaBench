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
struct comedi_isadma_desc {int /*<<< orphan*/  chan; } ;
struct comedi_isadma {struct comedi_isadma_desc* desc; } ;
struct comedi_device {struct dt282x_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_isadma_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dt282x_disable_dma(struct comedi_device *dev)
{
	struct dt282x_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc;
	int i;

	for (i = 0; i < 2; i++) {
		desc = &dma->desc[i];
		comedi_isadma_disable(desc->chan);
	}
}