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
typedef  int /*<<< orphan*/  u32 ;
struct msr {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int wrmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int msr_write(u32 msr, struct msr *m)
{
	return wrmsrl_safe(msr, m->q);
}