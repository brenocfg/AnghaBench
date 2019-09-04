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
typedef  int u8 ;
struct qedr_dev {int dummy; } ;
struct ib_port_modify {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int) ; 
 int EINVAL ; 
 struct qedr_dev* get_qedr_dev (struct ib_device*) ; 

int qedr_modify_port(struct ib_device *ibdev, u8 port, int mask,
		     struct ib_port_modify *props)
{
	struct qedr_dev *dev;

	dev = get_qedr_dev(ibdev);
	if (port > 1) {
		DP_ERR(dev, "invalid_port=0x%x\n", port);
		return -EINVAL;
	}

	return 0;
}