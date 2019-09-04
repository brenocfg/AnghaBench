#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmp_pdma_phy {struct mmp_pdma_chan* vchan; } ;
struct mmp_pdma_device {int dma_channels; int /*<<< orphan*/  phy_lock; struct mmp_pdma_phy* phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct mmp_pdma_chan {TYPE_1__ chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mmp_pdma_device* to_mmp_pdma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mmp_pdma_phy *lookup_phy(struct mmp_pdma_chan *pchan)
{
	int prio, i;
	struct mmp_pdma_device *pdev = to_mmp_pdma_dev(pchan->chan.device);
	struct mmp_pdma_phy *phy, *found = NULL;
	unsigned long flags;

	/*
	 * dma channel priorities
	 * ch 0 - 3,  16 - 19  <--> (0)
	 * ch 4 - 7,  20 - 23  <--> (1)
	 * ch 8 - 11, 24 - 27  <--> (2)
	 * ch 12 - 15, 28 - 31  <--> (3)
	 */

	spin_lock_irqsave(&pdev->phy_lock, flags);
	for (prio = 0; prio <= ((pdev->dma_channels - 1) & 0xf) >> 2; prio++) {
		for (i = 0; i < pdev->dma_channels; i++) {
			if (prio != (i & 0xf) >> 2)
				continue;
			phy = &pdev->phy[i];
			if (!phy->vchan) {
				phy->vchan = pchan;
				found = phy;
				goto out_unlock;
			}
		}
	}

out_unlock:
	spin_unlock_irqrestore(&pdev->phy_lock, flags);
	return found;
}