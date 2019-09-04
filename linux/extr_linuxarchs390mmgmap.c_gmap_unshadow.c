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
struct gmap {int removed; int asce; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int _ASCE_ORIGIN ; 
 int _ASCE_TYPE_MASK ; 
#define  _ASCE_TYPE_REGION1 131 
#define  _ASCE_TYPE_REGION2 130 
#define  _ASCE_TYPE_REGION3 129 
#define  _ASCE_TYPE_SEGMENT 128 
 int /*<<< orphan*/  __gmap_unshadow_r1t (struct gmap*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  __gmap_unshadow_r2t (struct gmap*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  __gmap_unshadow_r3t (struct gmap*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  __gmap_unshadow_sgt (struct gmap*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  gmap_call_notifier (struct gmap*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  gmap_flush_tlb (struct gmap*) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 

__attribute__((used)) static void gmap_unshadow(struct gmap *sg)
{
	unsigned long *table;

	BUG_ON(!gmap_is_shadow(sg));
	if (sg->removed)
		return;
	sg->removed = 1;
	gmap_call_notifier(sg, 0, -1UL);
	gmap_flush_tlb(sg);
	table = (unsigned long *)(sg->asce & _ASCE_ORIGIN);
	switch (sg->asce & _ASCE_TYPE_MASK) {
	case _ASCE_TYPE_REGION1:
		__gmap_unshadow_r1t(sg, 0, table);
		break;
	case _ASCE_TYPE_REGION2:
		__gmap_unshadow_r2t(sg, 0, table);
		break;
	case _ASCE_TYPE_REGION3:
		__gmap_unshadow_r3t(sg, 0, table);
		break;
	case _ASCE_TYPE_SEGMENT:
		__gmap_unshadow_sgt(sg, 0, table);
		break;
	}
}