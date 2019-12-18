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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ __get_latch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __check_latch(u16 port, u8 val)
{
	if (__get_latch(port) == val)
		return 0;
	return -EINVAL;
}