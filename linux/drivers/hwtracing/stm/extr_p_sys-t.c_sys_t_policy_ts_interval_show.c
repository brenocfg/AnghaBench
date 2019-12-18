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
struct sys_t_policy_node {int /*<<< orphan*/  ts_interval; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sys_t_policy_node* to_pdrv_policy_node (struct config_item*) ; 

__attribute__((used)) static ssize_t sys_t_policy_ts_interval_show(struct config_item *item,
					     char *page)
{
	struct sys_t_policy_node *pn = to_pdrv_policy_node(item);

	return sprintf(page, "%u\n", jiffies_to_msecs(pn->ts_interval));
}