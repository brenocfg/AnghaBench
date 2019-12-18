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
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct config_group*) ; 
 struct config_group* to_config_group (struct config_item*) ; 

__attribute__((used)) static void uvcg_config_item_release(struct config_item *item)
{
	struct config_group *group = to_config_group(item);

	kfree(group);
}