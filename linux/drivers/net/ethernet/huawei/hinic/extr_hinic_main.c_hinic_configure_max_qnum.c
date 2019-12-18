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
struct hinic_dev {TYPE_2__* hwdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_qps; } ;
struct TYPE_4__ {TYPE_1__ nic_cap; } ;

/* Variables and functions */
 int hinic_set_max_qnum (struct hinic_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hinic_configure_max_qnum(struct hinic_dev *nic_dev)
{
	int err;

	err = hinic_set_max_qnum(nic_dev, nic_dev->hwdev->nic_cap.max_qps);
	if (err)
		return err;

	return 0;
}