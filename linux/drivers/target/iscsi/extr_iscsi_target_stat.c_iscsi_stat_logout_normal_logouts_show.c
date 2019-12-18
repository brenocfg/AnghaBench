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
struct iscsi_logout_stats {int normal_logouts; } ;
struct iscsi_tiqn {struct iscsi_logout_stats logout_stats; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct iscsi_tiqn* iscsi_logout_stat_tiqn (struct config_item*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t iscsi_stat_logout_normal_logouts_show(struct config_item *item,
		char *page)
{
	struct iscsi_tiqn *tiqn = iscsi_logout_stat_tiqn(item);
	struct iscsi_logout_stats *lstats = &tiqn->logout_stats;

	return snprintf(page, PAGE_SIZE, "%u\n", lstats->normal_logouts);
}