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
struct be_adapter {int /*<<< orphan*/ * uc_list; int /*<<< orphan*/ * mc_list; int /*<<< orphan*/ * pmac_id; int /*<<< orphan*/  if_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cmd_if_destroy (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void be_if_destroy(struct be_adapter *adapter)
{
	be_cmd_if_destroy(adapter, adapter->if_handle,  0);

	kfree(adapter->pmac_id);
	adapter->pmac_id = NULL;

	kfree(adapter->mc_list);
	adapter->mc_list = NULL;

	kfree(adapter->uc_list);
	adapter->uc_list = NULL;
}