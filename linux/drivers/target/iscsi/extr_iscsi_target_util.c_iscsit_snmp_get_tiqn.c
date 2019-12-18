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
struct iscsi_tiqn {int dummy; } ;
struct iscsi_portal_group {struct iscsi_tiqn* tpg_tiqn; } ;
struct iscsi_conn {struct iscsi_portal_group* tpg; } ;

/* Variables and functions */

struct iscsi_tiqn *iscsit_snmp_get_tiqn(struct iscsi_conn *conn)
{
	struct iscsi_portal_group *tpg;

	if (!conn)
		return NULL;

	tpg = conn->tpg;
	if (!tpg)
		return NULL;

	if (!tpg->tpg_tiqn)
		return NULL;

	return tpg->tpg_tiqn;
}