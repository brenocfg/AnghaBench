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
struct kfd_dev {int dummy; } ;
struct kernel_queue {int dummy; } ;
typedef  enum kfd_queue_type { ____Placeholder_kfd_queue_type } kfd_queue_type ;

/* Variables and functions */

__attribute__((used)) static bool initialize_cik(struct kernel_queue *kq, struct kfd_dev *dev,
			enum kfd_queue_type type, unsigned int queue_size)
{
	return true;
}