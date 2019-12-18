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
struct hl_device {TYPE_1__* asic_funcs; } ;
struct hl_cb {int /*<<< orphan*/  bus_address; scalar_t__ kernel_address; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* asic_dma_free_coherent ) (struct hl_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hl_cb*) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cb_fini(struct hl_device *hdev, struct hl_cb *cb)
{
	hdev->asic_funcs->asic_dma_free_coherent(hdev, cb->size,
			(void *) (uintptr_t) cb->kernel_address,
			cb->bus_address);
	kfree(cb);
}