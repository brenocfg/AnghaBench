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
struct nullb_device {int /*<<< orphan*/  badblocks; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  badblocks_show (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct nullb_device* to_nullb_device (struct config_item*) ; 

__attribute__((used)) static ssize_t nullb_device_badblocks_show(struct config_item *item, char *page)
{
	struct nullb_device *t_dev = to_nullb_device(item);

	return badblocks_show(&t_dev->badblocks, page, 0);
}