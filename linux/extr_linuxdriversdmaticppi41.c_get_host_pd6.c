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

/* Variables and functions */
 int /*<<< orphan*/  DESC_PD_COMPLETE ; 

__attribute__((used)) static u32 get_host_pd6(u32 length)
{
	u32 reg;

	/* PD6 buffer size */
	reg = DESC_PD_COMPLETE;
	reg |= length;

	return reg;
}