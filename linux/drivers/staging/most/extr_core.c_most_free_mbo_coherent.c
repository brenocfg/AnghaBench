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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ extra_len; scalar_t__ buffer_size; } ;
struct most_channel {int /*<<< orphan*/  cleanup; int /*<<< orphan*/  mbo_ref; TYPE_2__* iface; TYPE_1__ cfg; } ;
struct mbo {struct mbo* virt_address; struct most_channel* context; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dma_free ) (struct mbo*,scalar_t__ const) ;} ;

/* Variables and functions */
 scalar_t__ atomic_sub_and_test (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mbo*) ; 
 int /*<<< orphan*/  stub1 (struct mbo*,scalar_t__ const) ; 

__attribute__((used)) static void most_free_mbo_coherent(struct mbo *mbo)
{
	struct most_channel *c = mbo->context;
	u16 const coherent_buf_size = c->cfg.buffer_size + c->cfg.extra_len;

	if (c->iface->dma_free)
		c->iface->dma_free(mbo, coherent_buf_size);
	else
		kfree(mbo->virt_address);
	kfree(mbo);
	if (atomic_sub_and_test(1, &c->mbo_ref))
		complete(&c->cleanup);
}