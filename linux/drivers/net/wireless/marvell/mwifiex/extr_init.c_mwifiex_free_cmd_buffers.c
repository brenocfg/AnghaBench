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
struct mwifiex_adapter {scalar_t__ sleep_cfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_free_cmd_buffer (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_invalidate_lists (struct mwifiex_adapter*) ; 

void mwifiex_free_cmd_buffers(struct mwifiex_adapter *adapter)
{
	mwifiex_invalidate_lists(adapter);

	/* Free command buffer */
	mwifiex_dbg(adapter, INFO, "info: free cmd buffer\n");
	mwifiex_free_cmd_buffer(adapter);

	if (adapter->sleep_cfm)
		dev_kfree_skb_any(adapter->sleep_cfm);
}