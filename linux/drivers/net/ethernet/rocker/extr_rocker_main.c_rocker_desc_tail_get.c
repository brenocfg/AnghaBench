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
struct rocker_dma_ring_info {size_t tail; size_t head; int /*<<< orphan*/  size; struct rocker_desc_info* desc_info; } ;
struct rocker_desc_info {TYPE_1__* desc; int /*<<< orphan*/  tlv_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  tlv_size; } ;

/* Variables and functions */
 size_t __pos_inc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_desc_gen (struct rocker_desc_info*) ; 

__attribute__((used)) static struct rocker_desc_info *
rocker_desc_tail_get(struct rocker_dma_ring_info *info)
{
	struct rocker_desc_info *desc_info;

	if (info->tail == info->head)
		return NULL; /* nothing to be done between head and tail */
	desc_info = &info->desc_info[info->tail];
	if (!rocker_desc_gen(desc_info))
		return NULL; /* gen bit not set, desc is not ready yet */
	info->tail = __pos_inc(info->tail, info->size);
	desc_info->tlv_size = desc_info->desc->tlv_size;
	return desc_info;
}