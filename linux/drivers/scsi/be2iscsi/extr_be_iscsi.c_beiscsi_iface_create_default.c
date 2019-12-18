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
struct beiscsi_hba {int dummy; } ;
struct be_cmd_get_if_info_resp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_IP_TYPE_V4 ; 
 int /*<<< orphan*/  BEISCSI_IP_TYPE_V6 ; 
 int /*<<< orphan*/  beiscsi_if_get_info (struct beiscsi_hba*,int /*<<< orphan*/ ,struct be_cmd_get_if_info_resp**) ; 
 int /*<<< orphan*/  beiscsi_iface_create_ipv4 (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_iface_create_ipv6 (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  kfree (struct be_cmd_get_if_info_resp*) ; 

void beiscsi_iface_create_default(struct beiscsi_hba *phba)
{
	struct be_cmd_get_if_info_resp *if_info;

	if (!beiscsi_if_get_info(phba, BEISCSI_IP_TYPE_V4, &if_info)) {
		beiscsi_iface_create_ipv4(phba);
		kfree(if_info);
	}

	if (!beiscsi_if_get_info(phba, BEISCSI_IP_TYPE_V6, &if_info)) {
		beiscsi_iface_create_ipv6(phba);
		kfree(if_info);
	}
}