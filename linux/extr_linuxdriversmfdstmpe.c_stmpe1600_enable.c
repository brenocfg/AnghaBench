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
struct stmpe {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int STMPE_BLOCK_GPIO ; 

__attribute__((used)) static int stmpe1600_enable(struct stmpe *stmpe, unsigned int blocks,
			   bool enable)
{
	if (blocks & STMPE_BLOCK_GPIO)
		return 0;
	else
		return -EINVAL;
}