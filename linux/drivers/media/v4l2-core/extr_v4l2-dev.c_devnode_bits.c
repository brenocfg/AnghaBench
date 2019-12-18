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
typedef  enum vfl_devnode_type { ____Placeholder_vfl_devnode_type } vfl_devnode_type ;

/* Variables and functions */
 unsigned long** devnode_nums ; 

__attribute__((used)) static inline unsigned long *devnode_bits(enum vfl_devnode_type vfl_type)
{
	return devnode_nums[vfl_type];
}