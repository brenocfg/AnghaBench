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
struct ehea_mr {struct ehea_adapter* adapter; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  handle; } ;
struct ehea_adapter {int /*<<< orphan*/  pd; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_MR_ACC_CTRL ; 
 int EIO ; 
 scalar_t__ H_SUCCESS ; 
 scalar_t__ ehea_h_register_smr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ehea_mr*) ; 

int ehea_gen_smr(struct ehea_adapter *adapter, struct ehea_mr *old_mr,
		 struct ehea_mr *shared_mr)
{
	u64 hret;

	hret = ehea_h_register_smr(adapter->handle, old_mr->handle,
				   old_mr->vaddr, EHEA_MR_ACC_CTRL,
				   adapter->pd, shared_mr);
	if (hret != H_SUCCESS)
		return -EIO;

	shared_mr->adapter = adapter;

	return 0;
}