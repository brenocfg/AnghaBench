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
typedef  unsigned int u32 ;
struct ib_vl_weight_elem {int vl; scalar_t__ weight; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void get_vlarb_preempt(struct hfi1_devdata *dd, u32 nelems,
			      struct ib_vl_weight_elem *vl)
{
	unsigned int i;

	for (i = 0; i < nelems; i++, vl++) {
		vl->vl = 0xf;
		vl->weight = 0;
	}
}