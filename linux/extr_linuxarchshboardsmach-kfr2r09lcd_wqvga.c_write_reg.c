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
struct sh_mobile_lcdc_sys_bus_ops {int /*<<< orphan*/  (* write_index ) (void*,unsigned long) ;int /*<<< orphan*/  (* write_data ) (void*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,unsigned long) ; 
 int /*<<< orphan*/  stub2 (void*,unsigned long) ; 

__attribute__((used)) static void write_reg(void *sohandle,
		      struct sh_mobile_lcdc_sys_bus_ops *so,
		      int i, unsigned long v)
{
	if (i)
		so->write_data(sohandle, v); /* PTH4/LCDRS High [param, 17:0] */
	else
		so->write_index(sohandle, v); /* PTH4/LCDRS Low [cmd, 7:0] */
}