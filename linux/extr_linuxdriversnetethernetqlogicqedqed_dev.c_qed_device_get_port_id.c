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
struct qed_dev {int dummy; } ;
struct TYPE_2__ {int abs_pf_id; } ;

/* Variables and functions */
 TYPE_1__* QED_LEADING_HWFN (struct qed_dev*) ; 
 int qed_device_num_ports (struct qed_dev*) ; 

int qed_device_get_port_id(struct qed_dev *cdev)
{
	return (QED_LEADING_HWFN(cdev)->abs_pf_id) % qed_device_num_ports(cdev);
}