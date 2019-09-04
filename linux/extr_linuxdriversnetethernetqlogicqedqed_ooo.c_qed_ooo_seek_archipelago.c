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
typedef  int u32 ;
struct qed_ooo_info {int cid_base; int max_num_archipelagos; struct qed_ooo_archipelago* p_archipelagos_mem; } ;
struct qed_ooo_archipelago {int /*<<< orphan*/  isles_list; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qed_ooo_archipelago
*qed_ooo_seek_archipelago(struct qed_hwfn *p_hwfn,
			  struct qed_ooo_info
			  *p_ooo_info,
			  u32 cid)
{
	u32 idx = (cid & 0xffff) - p_ooo_info->cid_base;
	struct qed_ooo_archipelago *p_archipelago;

	if (idx >= p_ooo_info->max_num_archipelagos)
		return NULL;

	p_archipelago = &p_ooo_info->p_archipelagos_mem[idx];

	if (list_empty(&p_archipelago->isles_list))
		return NULL;

	return p_archipelago;
}