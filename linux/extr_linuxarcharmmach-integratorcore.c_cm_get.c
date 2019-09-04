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
 scalar_t__ INTEGRATOR_HDR_CTRL_OFFSET ; 
 scalar_t__ cm_base ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

u32 cm_get(void)
{
	return readl(cm_base + INTEGRATOR_HDR_CTRL_OFFSET);
}