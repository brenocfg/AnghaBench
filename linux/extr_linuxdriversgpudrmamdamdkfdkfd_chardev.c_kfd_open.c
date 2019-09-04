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
struct kfd_process {int /*<<< orphan*/  is_32bit_user_mode; int /*<<< orphan*/  pasid; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct kfd_process*) ; 
 int PTR_ERR (struct kfd_process*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ iminor (struct inode*) ; 
 int in_compat_syscall () ; 
 struct kfd_process* kfd_create_process (struct file*) ; 
 int /*<<< orphan*/  kfd_device ; 
 scalar_t__ kfd_is_locked () ; 

__attribute__((used)) static int kfd_open(struct inode *inode, struct file *filep)
{
	struct kfd_process *process;
	bool is_32bit_user_mode;

	if (iminor(inode) != 0)
		return -ENODEV;

	is_32bit_user_mode = in_compat_syscall();

	if (is_32bit_user_mode) {
		dev_warn(kfd_device,
			"Process %d (32-bit) failed to open /dev/kfd\n"
			"32-bit processes are not supported by amdkfd\n",
			current->pid);
		return -EPERM;
	}

	process = kfd_create_process(filep);
	if (IS_ERR(process))
		return PTR_ERR(process);

	if (kfd_is_locked())
		return -EAGAIN;

	dev_dbg(kfd_device, "process %d opened, compat mode (32 bit) - %d\n",
		process->pasid, process->is_32bit_user_mode);

	return 0;
}