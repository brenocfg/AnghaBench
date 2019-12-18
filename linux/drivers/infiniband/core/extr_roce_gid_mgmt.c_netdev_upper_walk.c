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
struct upper_list {struct net_device* upper; int /*<<< orphan*/  list; } ;
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct upper_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int netdev_upper_walk(struct net_device *upper, void *data)
{
	struct upper_list *entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
	struct list_head *upper_list = data;

	if (!entry)
		return 0;

	list_add_tail(&entry->list, upper_list);
	dev_hold(upper);
	entry->upper = upper;

	return 0;
}