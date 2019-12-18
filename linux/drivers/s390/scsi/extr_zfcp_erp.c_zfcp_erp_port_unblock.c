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
struct zfcp_port {int /*<<< orphan*/  status; int /*<<< orphan*/  erp_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_UNBLOCKED ; 
 int /*<<< orphan*/  atomic_or (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_run (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfcp_erp_status_change_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfcp_erp_port_unblock(struct zfcp_port *port)
{
	if (zfcp_erp_status_change_set(ZFCP_STATUS_COMMON_UNBLOCKED,
				       &port->status))
		zfcp_dbf_rec_run("erpubl1", &port->erp_action);
	atomic_or(ZFCP_STATUS_COMMON_UNBLOCKED, &port->status);
}