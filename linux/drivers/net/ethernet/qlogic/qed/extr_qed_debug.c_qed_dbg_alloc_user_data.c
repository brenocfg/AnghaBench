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
struct qed_hwfn {int /*<<< orphan*/  dbg_user_info; } ;
struct dbg_tools_user_data {int dummy; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int DBG_STATUS_OK ; 
 int DBG_STATUS_VIRT_MEM_ALLOC_FAILED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 

enum dbg_status qed_dbg_alloc_user_data(struct qed_hwfn *p_hwfn)
{
	p_hwfn->dbg_user_info = kzalloc(sizeof(struct dbg_tools_user_data),
					GFP_KERNEL);
	if (!p_hwfn->dbg_user_info)
		return DBG_STATUS_VIRT_MEM_ALLOC_FAILED;

	return DBG_STATUS_OK;
}