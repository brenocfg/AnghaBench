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
struct dma_domain {int dummy; } ;
struct vmd_dev {TYPE_1__* dev; struct dma_domain dma_domain; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_dma_domain (struct dma_domain*) ; 
 scalar_t__ get_dma_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmd_teardown_dma_ops(struct vmd_dev *vmd)
{
	struct dma_domain *domain = &vmd->dma_domain;

	if (get_dma_ops(&vmd->dev->dev))
		del_dma_domain(domain);
}