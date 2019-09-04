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
struct owl_dma_vchan {int dummy; } ;
struct owl_dma_pchan {int /*<<< orphan*/  lock; struct owl_dma_vchan* vchan; } ;
struct owl_dma {int nr_pchans; struct owl_dma_pchan* pchans; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct owl_dma_pchan *owl_dma_get_pchan(struct owl_dma *od,
					       struct owl_dma_vchan *vchan)
{
	struct owl_dma_pchan *pchan = NULL;
	unsigned long flags;
	int i;

	for (i = 0; i < od->nr_pchans; i++) {
		pchan = &od->pchans[i];

		spin_lock_irqsave(&pchan->lock, flags);
		if (!pchan->vchan) {
			pchan->vchan = vchan;
			spin_unlock_irqrestore(&pchan->lock, flags);
			break;
		}

		spin_unlock_irqrestore(&pchan->lock, flags);
	}

	return pchan;
}