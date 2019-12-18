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
struct target_backend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  target_core_setup_dev_action_cit (struct target_backend*) ; 
 int /*<<< orphan*/  target_core_setup_dev_alua_tg_pt_gps_cit (struct target_backend*) ; 
 int /*<<< orphan*/  target_core_setup_dev_attrib_cit (struct target_backend*) ; 
 int /*<<< orphan*/  target_core_setup_dev_cit (struct target_backend*) ; 
 int /*<<< orphan*/  target_core_setup_dev_pr_cit (struct target_backend*) ; 
 int /*<<< orphan*/  target_core_setup_dev_stat_cit (struct target_backend*) ; 
 int /*<<< orphan*/  target_core_setup_dev_wwn_cit (struct target_backend*) ; 

void target_setup_backend_cits(struct target_backend *tb)
{
	target_core_setup_dev_cit(tb);
	target_core_setup_dev_action_cit(tb);
	target_core_setup_dev_attrib_cit(tb);
	target_core_setup_dev_pr_cit(tb);
	target_core_setup_dev_wwn_cit(tb);
	target_core_setup_dev_alua_tg_pt_gps_cit(tb);
	target_core_setup_dev_stat_cit(tb);
}