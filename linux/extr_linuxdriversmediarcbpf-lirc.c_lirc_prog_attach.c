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
union bpf_attr {int /*<<< orphan*/  target_fd; scalar_t__ attach_flags; } ;
struct rc_dev {int /*<<< orphan*/  dev; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct rc_dev*) ; 
 int PTR_ERR (struct rc_dev*) ; 
 int lirc_bpf_attach (struct rc_dev*,struct bpf_prog*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct rc_dev* rc_dev_get_from_fd (int /*<<< orphan*/ ) ; 

int lirc_prog_attach(const union bpf_attr *attr, struct bpf_prog *prog)
{
	struct rc_dev *rcdev;
	int ret;

	if (attr->attach_flags)
		return -EINVAL;

	rcdev = rc_dev_get_from_fd(attr->target_fd);
	if (IS_ERR(rcdev))
		return PTR_ERR(rcdev);

	ret = lirc_bpf_attach(rcdev, prog);

	put_device(&rcdev->dev);

	return ret;
}