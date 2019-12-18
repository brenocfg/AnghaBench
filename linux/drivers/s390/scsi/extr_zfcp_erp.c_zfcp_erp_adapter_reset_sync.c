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
struct zfcp_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_RUNNING ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_set_adapter_status (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 

void zfcp_erp_adapter_reset_sync(struct zfcp_adapter *adapter, char *dbftag)
{
	zfcp_erp_set_adapter_status(adapter, ZFCP_STATUS_COMMON_RUNNING);
	zfcp_erp_adapter_reopen(adapter, ZFCP_STATUS_COMMON_ERP_FAILED, dbftag);
	zfcp_erp_wait(adapter);
}