#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mode; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  store; TYPE_2__ attr; } ;
struct sg_attr {int handle; TYPE_1__ attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  store; int /*<<< orphan*/  attr_name; } ;

/* Variables and functions */
 TYPE_3__* ops_info ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

__attribute__((used)) static void add_attr(int handle, struct sg_attr *attr, int index)
{
	attr->handle = handle;
	sysfs_attr_init(&attr->attr.attr);
	attr->attr.attr.name = ops_info[index].attr_name;
	attr->attr.attr.mode = 0220;
	attr->attr.store = ops_info[index].store;
}