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
struct kfd_process {int dummy; } ;
struct kfd_ioctl_get_version_args {int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KFD_IOCTL_MAJOR_VERSION ; 
 int /*<<< orphan*/  KFD_IOCTL_MINOR_VERSION ; 

__attribute__((used)) static int kfd_ioctl_get_version(struct file *filep, struct kfd_process *p,
					void *data)
{
	struct kfd_ioctl_get_version_args *args = data;

	args->major_version = KFD_IOCTL_MAJOR_VERSION;
	args->minor_version = KFD_IOCTL_MINOR_VERSION;

	return 0;
}