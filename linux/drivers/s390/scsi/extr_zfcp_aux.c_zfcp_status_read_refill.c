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
struct zfcp_adapter {scalar_t__ stat_read_buf_num; int /*<<< orphan*/  stat_miss; int /*<<< orphan*/  qdio; } ;

/* Variables and functions */
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zfcp_fsf_status_read (int /*<<< orphan*/ ) ; 

int zfcp_status_read_refill(struct zfcp_adapter *adapter)
{
	while (atomic_add_unless(&adapter->stat_miss, -1, 0))
		if (zfcp_fsf_status_read(adapter->qdio)) {
			atomic_inc(&adapter->stat_miss); /* undo add -1 */
			if (atomic_read(&adapter->stat_miss) >=
			    adapter->stat_read_buf_num) {
				zfcp_erp_adapter_reopen(adapter, 0, "axsref1");
				return 1;
			}
			break;
		}
	return 0;
}