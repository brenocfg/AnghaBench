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
struct xvip_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xvip_read (struct xvip_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xvip_write (struct xvip_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xvip_clr_and_set(struct xvip_device *xvip, u32 addr, u32 clr, u32 set)
{
	u32 reg;

	reg = xvip_read(xvip, addr);
	reg &= ~clr;
	reg |= set;
	xvip_write(xvip, addr, reg);
}