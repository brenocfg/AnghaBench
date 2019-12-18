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
typedef  scalar_t__ u64 ;
struct nvkm_vma {scalar_t__ size; scalar_t__ addr; int /*<<< orphan*/  head; int /*<<< orphan*/  mapped; int /*<<< orphan*/  busy; int /*<<< orphan*/  user; int /*<<< orphan*/  part; int /*<<< orphan*/  used; int /*<<< orphan*/  refd; int /*<<< orphan*/  page; int /*<<< orphan*/  sparse; int /*<<< orphan*/  mapref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nvkm_vma* nvkm_vma_new (scalar_t__,scalar_t__) ; 

struct nvkm_vma *
nvkm_vma_tail(struct nvkm_vma *vma, u64 tail)
{
	struct nvkm_vma *new;

	BUG_ON(vma->size == tail);

	if (!(new = nvkm_vma_new(vma->addr + (vma->size - tail), tail)))
		return NULL;
	vma->size -= tail;

	new->mapref = vma->mapref;
	new->sparse = vma->sparse;
	new->page = vma->page;
	new->refd = vma->refd;
	new->used = vma->used;
	new->part = vma->part;
	new->user = vma->user;
	new->busy = vma->busy;
	new->mapped = vma->mapped;
	list_add(&new->head, &vma->head);
	return new;
}