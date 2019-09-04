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
struct qed_hwfn {int dummy; } ;
struct qed_bmap {scalar_t__ max_count; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

void qed_bmap_set_id(struct qed_hwfn *p_hwfn,
		     struct qed_bmap *bmap, u32 id_num)
{
	if (id_num >= bmap->max_count)
		return;

	__set_bit(id_num, bmap->bitmap);
}