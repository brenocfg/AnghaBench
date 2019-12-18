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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  core_alua_show_implicit_trans_secs (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  to_tg_pt_gp (struct config_item*) ; 

__attribute__((used)) static ssize_t target_tg_pt_gp_implicit_trans_secs_show(
		struct config_item *item, char *page)
{
	return core_alua_show_implicit_trans_secs(to_tg_pt_gp(item), page);
}