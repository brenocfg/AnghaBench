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
typedef  scalar_t__ u32 ;
struct nvkm_mm_node {scalar_t__ length; scalar_t__ offset; scalar_t__ type; int /*<<< orphan*/  fl_entry; int /*<<< orphan*/  nl_entry; int /*<<< orphan*/  heap; } ;
struct nvkm_mm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NVKM_MM_TYPE_NONE ; 
 struct nvkm_mm_node* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nvkm_mm_node *
region_tail(struct nvkm_mm *mm, struct nvkm_mm_node *a, u32 size)
{
	struct nvkm_mm_node *b;

	if (a->length == size)
		return a;

	b = kmalloc(sizeof(*b), GFP_KERNEL);
	if (unlikely(b == NULL))
		return NULL;

	a->length -= size;
	b->offset  = a->offset + a->length;
	b->length  = size;
	b->heap    = a->heap;
	b->type    = a->type;

	list_add(&b->nl_entry, &a->nl_entry);
	if (b->type == NVKM_MM_TYPE_NONE)
		list_add(&b->fl_entry, &a->fl_entry);

	return b;
}