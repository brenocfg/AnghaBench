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
struct SIS_OH {scalar_t__ size; int /*<<< orphan*/  offset; struct SIS_OH* poh_next; } ;
struct SIS_HEAP {scalar_t__ max_freesize; struct SIS_OH oh_used; struct SIS_OH oh_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 
 int /*<<< orphan*/  sisfb_delete_node (struct SIS_OH*) ; 
 int /*<<< orphan*/  sisfb_insert_node (struct SIS_OH*,struct SIS_OH*) ; 
 struct SIS_OH* sisfb_poh_new_node (struct SIS_HEAP*) ; 

__attribute__((used)) static struct SIS_OH *
sisfb_poh_allocate(struct SIS_HEAP *memheap, u32 size)
{
	struct SIS_OH	*pohThis;
	struct SIS_OH	*pohRoot;
	int		bAllocated = 0;

	if(size > memheap->max_freesize) {
		DPRINTK("sisfb: Can't allocate %dk video memory\n",
			(unsigned int) size / 1024);
		return NULL;
	}

	pohThis = memheap->oh_free.poh_next;

	while(pohThis != &memheap->oh_free) {
		if(size <= pohThis->size) {
			bAllocated = 1;
			break;
		}
		pohThis = pohThis->poh_next;
	}

	if(!bAllocated) {
		DPRINTK("sisfb: Can't allocate %dk video memory\n",
			(unsigned int) size / 1024);
		return NULL;
	}

	if(size == pohThis->size) {
		pohRoot = pohThis;
		sisfb_delete_node(pohThis);
	} else {
		pohRoot = sisfb_poh_new_node(memheap);
		if(pohRoot == NULL)
			return NULL;

		pohRoot->offset = pohThis->offset;
		pohRoot->size = size;

		pohThis->offset += size;
		pohThis->size -= size;
	}

	memheap->max_freesize -= size;

	pohThis = &memheap->oh_used;
	sisfb_insert_node(pohThis, pohRoot);

	return pohRoot;
}