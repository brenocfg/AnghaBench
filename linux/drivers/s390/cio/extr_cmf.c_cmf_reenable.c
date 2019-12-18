#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ccw_device {int dummy; } ;
struct TYPE_2__ {int (* set ) (struct ccw_device*,int) ;int /*<<< orphan*/  (* reset ) (struct ccw_device*) ;} ;

/* Variables and functions */
 TYPE_1__* cmbops ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*) ; 
 int stub2 (struct ccw_device*,int) ; 

int cmf_reenable(struct ccw_device *cdev)
{
	cmbops->reset(cdev);
	return cmbops->set(cdev, 2);
}