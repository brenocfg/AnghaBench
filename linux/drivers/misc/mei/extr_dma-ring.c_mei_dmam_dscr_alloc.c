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
struct mei_dma_dscr {scalar_t__ vaddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  size; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ dmam_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mei_dmam_dscr_alloc(struct mei_device *dev,
			       struct mei_dma_dscr *dscr)
{
	if (!dscr->size)
		return 0;

	if (WARN_ON(!is_power_of_2(dscr->size)))
		return -EINVAL;

	if (dscr->vaddr)
		return 0;

	dscr->vaddr = dmam_alloc_coherent(dev->dev, dscr->size, &dscr->daddr,
					  GFP_KERNEL);
	if (!dscr->vaddr)
		return -ENOMEM;

	return 0;
}