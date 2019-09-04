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
struct dispc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_SYSCONFIG ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dispc_device*,int /*<<< orphan*/ ,int,int,int) ; 

void dispc_enable_sidle(struct dispc_device *dispc)
{
	/* SIDLEMODE: smart idle */
	REG_FLD_MOD(dispc, DISPC_SYSCONFIG, 2, 4, 3);
}