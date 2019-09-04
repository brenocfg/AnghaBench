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
struct shdma_chan {int irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_irq ; 
 int /*<<< orphan*/  chan_irqt ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,char const*,struct shdma_chan*) ; 

int shdma_request_irq(struct shdma_chan *schan, int irq,
			   unsigned long flags, const char *name)
{
	int ret = devm_request_threaded_irq(schan->dev, irq, chan_irq,
					    chan_irqt, flags, name, schan);

	schan->irq = ret < 0 ? ret : irq;

	return ret;
}