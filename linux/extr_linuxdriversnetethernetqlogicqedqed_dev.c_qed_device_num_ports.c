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
struct qed_dev {int num_hwfns; int num_ports_in_engine; } ;

/* Variables and functions */
 int qed_device_num_engines (struct qed_dev*) ; 

__attribute__((used)) static int qed_device_num_ports(struct qed_dev *cdev)
{
	/* in CMT always only one port */
	if (cdev->num_hwfns > 1)
		return 1;

	return cdev->num_ports_in_engine * qed_device_num_engines(cdev);
}