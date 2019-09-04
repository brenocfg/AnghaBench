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
struct TYPE_2__ {int /*<<< orphan*/  global_mmio_bar; int /*<<< orphan*/  pp_mmio_bar; } ;
struct ocxl_afu {TYPE_1__ config; int /*<<< orphan*/  fn; scalar_t__ pp_mmio_start; scalar_t__ global_mmio_start; int /*<<< orphan*/ * global_mmio_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_fn_bar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmap_mmio_areas(struct ocxl_afu *afu)
{
	if (afu->global_mmio_ptr) {
		iounmap(afu->global_mmio_ptr);
		afu->global_mmio_ptr = NULL;
	}
	afu->global_mmio_start = 0;
	afu->pp_mmio_start = 0;
	release_fn_bar(afu->fn, afu->config.pp_mmio_bar);
	release_fn_bar(afu->fn, afu->config.global_mmio_bar);
}