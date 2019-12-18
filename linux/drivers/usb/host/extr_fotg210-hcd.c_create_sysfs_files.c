#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fotg210_hcd {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_uframe_periodic_max ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 TYPE_2__* fotg210_to_hcd (struct fotg210_hcd*) ; 

__attribute__((used)) static inline int create_sysfs_files(struct fotg210_hcd *fotg210)
{
	struct device *controller = fotg210_to_hcd(fotg210)->self.controller;

	return device_create_file(controller, &dev_attr_uframe_periodic_max);
}