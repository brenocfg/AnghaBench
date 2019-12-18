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
 int /*<<< orphan*/  target_show_dynamic_sessions (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  to_tpg (struct config_item*) ; 

__attribute__((used)) static ssize_t lio_target_tpg_dynamic_sessions_show(struct config_item *item,
		char *page)
{
	return target_show_dynamic_sessions(to_tpg(item), page);
}