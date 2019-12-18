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
struct etnaviv_cmdbuf_suballoc {int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  free_event; int /*<<< orphan*/  lock; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 struct etnaviv_cmdbuf_suballoc* ERR_PTR (int) ; 
 scalar_t__ ETNAVIV_SOFTPIN_START_ADDRESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SUBALLOC_SIZE ; 
 int /*<<< orphan*/  dma_alloc_wc (struct device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_cmdbuf_suballoc*) ; 
 struct etnaviv_cmdbuf_suballoc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct etnaviv_cmdbuf_suballoc *
etnaviv_cmdbuf_suballoc_new(struct device *dev)
{
	struct etnaviv_cmdbuf_suballoc *suballoc;
	int ret;

	suballoc = kzalloc(sizeof(*suballoc), GFP_KERNEL);
	if (!suballoc)
		return ERR_PTR(-ENOMEM);

	suballoc->dev = dev;
	mutex_init(&suballoc->lock);
	init_waitqueue_head(&suballoc->free_event);

	BUILD_BUG_ON(ETNAVIV_SOFTPIN_START_ADDRESS < SUBALLOC_SIZE);
	suballoc->vaddr = dma_alloc_wc(dev, SUBALLOC_SIZE,
				       &suballoc->paddr, GFP_KERNEL);
	if (!suballoc->vaddr) {
		ret = -ENOMEM;
		goto free_suballoc;
	}

	return suballoc;

free_suballoc:
	kfree(suballoc);

	return ERR_PTR(ret);
}