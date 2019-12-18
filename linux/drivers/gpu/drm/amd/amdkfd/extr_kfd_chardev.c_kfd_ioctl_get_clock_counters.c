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
struct kfd_ioctl_get_clock_counters_args {int system_clock_freq; int /*<<< orphan*/  system_clock_counter; int /*<<< orphan*/  cpu_clock_counter; scalar_t__ gpu_clock_counter; int /*<<< orphan*/  gpu_id; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ amdgpu_amdkfd_get_gpu_clock_counter (int /*<<< orphan*/ ) ; 
 struct kfd_dev* kfd_device_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  ktime_get_raw_ns () ; 

__attribute__((used)) static int kfd_ioctl_get_clock_counters(struct file *filep,
				struct kfd_process *p, void *data)
{
	struct kfd_ioctl_get_clock_counters_args *args = data;
	struct kfd_dev *dev;

	dev = kfd_device_by_id(args->gpu_id);
	if (dev)
		/* Reading GPU clock counter from KGD */
		args->gpu_clock_counter = amdgpu_amdkfd_get_gpu_clock_counter(dev->kgd);
	else
		/* Node without GPU resource */
		args->gpu_clock_counter = 0;

	/* No access to rdtsc. Using raw monotonic time */
	args->cpu_clock_counter = ktime_get_raw_ns();
	args->system_clock_counter = ktime_get_boottime_ns();

	/* Since the counter is in nano-seconds we use 1GHz frequency */
	args->system_clock_freq = 1000000000;

	return 0;
}