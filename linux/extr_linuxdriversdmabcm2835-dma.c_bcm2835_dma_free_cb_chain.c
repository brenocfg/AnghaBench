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
struct bcm2835_desc {size_t frames; TYPE_2__* cb_list; TYPE_1__* c; } ;
struct TYPE_4__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  cb; } ;
struct TYPE_3__ {int /*<<< orphan*/  cb_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bcm2835_desc*) ; 

__attribute__((used)) static void bcm2835_dma_free_cb_chain(struct bcm2835_desc *desc)
{
	size_t i;

	for (i = 0; i < desc->frames; i++)
		dma_pool_free(desc->c->cb_pool, desc->cb_list[i].cb,
			      desc->cb_list[i].paddr);

	kfree(desc);
}