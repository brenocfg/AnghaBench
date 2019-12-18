#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct t4_sq {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  queue; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  memsize; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct c4iw_rdev {TYPE_2__ lldi; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct t4_sq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_host_sq(struct c4iw_rdev *rdev, struct t4_sq *sq)
{
	sq->queue = dma_alloc_coherent(&(rdev->lldi.pdev->dev), sq->memsize,
				       &(sq->dma_addr), GFP_KERNEL);
	if (!sq->queue)
		return -ENOMEM;
	sq->phys_addr = virt_to_phys(sq->queue);
	dma_unmap_addr_set(sq, mapping, sq->dma_addr);
	return 0;
}