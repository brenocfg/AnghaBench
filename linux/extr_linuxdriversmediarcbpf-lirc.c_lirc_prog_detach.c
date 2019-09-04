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
union bpf_attr {int /*<<< orphan*/  target_fd; int /*<<< orphan*/  attach_bpf_fd; scalar_t__ attach_flags; } ;
struct rc_dev {int /*<<< orphan*/  dev; } ;
struct bpf_prog {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_LIRC_MODE2 ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct rc_dev*) ; 
 int PTR_ERR (struct rc_dev*) ; 
 struct rc_dev* bpf_prog_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_put (struct rc_dev*) ; 
 int lirc_bpf_detach (struct rc_dev*,struct rc_dev*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct rc_dev* rc_dev_get_from_fd (int /*<<< orphan*/ ) ; 

int lirc_prog_detach(const union bpf_attr *attr)
{
	struct bpf_prog *prog;
	struct rc_dev *rcdev;
	int ret;

	if (attr->attach_flags)
		return -EINVAL;

	prog = bpf_prog_get_type(attr->attach_bpf_fd,
				 BPF_PROG_TYPE_LIRC_MODE2);
	if (IS_ERR(prog))
		return PTR_ERR(prog);

	rcdev = rc_dev_get_from_fd(attr->target_fd);
	if (IS_ERR(rcdev)) {
		bpf_prog_put(prog);
		return PTR_ERR(rcdev);
	}

	ret = lirc_bpf_detach(rcdev, prog);

	bpf_prog_put(prog);
	put_device(&rcdev->dev);

	return ret;
}