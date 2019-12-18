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
struct iscsi_portal_group {int /*<<< orphan*/  param_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_print_params (int /*<<< orphan*/ ) ; 

void iscsit_tpg_dump_params(struct iscsi_portal_group *tpg)
{
	iscsi_print_params(tpg->param_list);
}