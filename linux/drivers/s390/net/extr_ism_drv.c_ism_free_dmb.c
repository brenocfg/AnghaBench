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
struct smcd_dmb {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  dmb_len; int /*<<< orphan*/  sba_idx; } ;
struct ism_dev {TYPE_1__* pdev; int /*<<< orphan*/  sba_bitmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ism_free_dmb(struct ism_dev *ism, struct smcd_dmb *dmb)
{
	clear_bit(dmb->sba_idx, ism->sba_bitmap);
	dma_free_coherent(&ism->pdev->dev, dmb->dmb_len,
			  dmb->cpu_addr, dmb->dma_addr);
}