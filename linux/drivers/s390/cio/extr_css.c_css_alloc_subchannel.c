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
struct subchannel_id {int dummy; } ;
struct TYPE_4__ {void** dma_mask; void* coherent_dma_mask; int /*<<< orphan*/ * release; } ;
struct TYPE_3__ {int /*<<< orphan*/  st; } ;
struct schib {TYPE_1__ pmcw; } ;
struct subchannel {void* dma_mask; TYPE_2__ dev; int /*<<< orphan*/  todo_work; int /*<<< orphan*/  st; struct schib schib; struct subchannel_id schid; } ;

/* Variables and functions */
 void* DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 struct subchannel* ERR_PTR (int) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int css_sch_create_locks (struct subchannel*) ; 
 int /*<<< orphan*/  css_sch_todo ; 
 int /*<<< orphan*/  css_subchannel_release ; 
 int css_validate_subchannel (struct subchannel_id,struct schib*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct subchannel*) ; 
 struct subchannel* kzalloc (int,int) ; 

struct subchannel *css_alloc_subchannel(struct subchannel_id schid,
					struct schib *schib)
{
	struct subchannel *sch;
	int ret;

	ret = css_validate_subchannel(schid, schib);
	if (ret < 0)
		return ERR_PTR(ret);

	sch = kzalloc(sizeof(*sch), GFP_KERNEL | GFP_DMA);
	if (!sch)
		return ERR_PTR(-ENOMEM);

	sch->schid = schid;
	sch->schib = *schib;
	sch->st = schib->pmcw.st;

	ret = css_sch_create_locks(sch);
	if (ret)
		goto err;

	INIT_WORK(&sch->todo_work, css_sch_todo);
	sch->dev.release = &css_subchannel_release;
	device_initialize(&sch->dev);
	/*
	 * The physical addresses of some the dma structures that can
	 * belong to a subchannel need to fit 31 bit width (e.g. ccw).
	 */
	sch->dev.coherent_dma_mask = DMA_BIT_MASK(31);
	/*
	 * But we don't have such restrictions imposed on the stuff that
	 * is handled by the streaming API.
	 */
	sch->dma_mask = DMA_BIT_MASK(64);
	sch->dev.dma_mask = &sch->dma_mask;
	return sch;

err:
	kfree(sch);
	return ERR_PTR(ret);
}