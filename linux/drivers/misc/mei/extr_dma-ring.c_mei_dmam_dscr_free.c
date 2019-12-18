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
struct mei_dma_dscr {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  size; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmam_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mei_dmam_dscr_free(struct mei_device *dev,
			       struct mei_dma_dscr *dscr)
{
	if (!dscr->vaddr)
		return;

	dmam_free_coherent(dev->dev, dscr->size, dscr->vaddr, dscr->daddr);
	dscr->vaddr = NULL;
}