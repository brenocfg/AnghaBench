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
 int /*<<< orphan*/  __NR_modify_ldt ; 
 int syscall (int /*<<< orphan*/ ,int,void*,unsigned long) ; 

__attribute__((used)) static inline int modify_ldt (int func, void *ptr, unsigned long bytecount)
{
	return syscall(__NR_modify_ldt, func, ptr, bytecount);
}