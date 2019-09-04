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
struct rvt_dev_info {int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */

__attribute__((used)) static inline int check_driver_override(struct rvt_dev_info *rdi,
					size_t offset, void *func)
{
	if (!*(void **)((void *)&rdi->ibdev + offset)) {
		*(void **)((void *)&rdi->ibdev + offset) = func;
		return 0;
	}

	return 1;
}