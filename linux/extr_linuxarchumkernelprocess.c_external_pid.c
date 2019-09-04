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

/* Variables and functions */
 int* userspace_pid ; 

__attribute__((used)) static inline int external_pid(void)
{
	/* FIXME: Need to look up userspace_pid by cpu */
	return userspace_pid[0];
}