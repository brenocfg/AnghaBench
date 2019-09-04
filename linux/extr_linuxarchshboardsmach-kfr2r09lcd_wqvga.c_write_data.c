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
struct sh_mobile_lcdc_sys_bus_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_reg (void*,struct sh_mobile_lcdc_sys_bus_ops*,int,unsigned char const) ; 

__attribute__((used)) static void write_data(void *sohandle,
		       struct sh_mobile_lcdc_sys_bus_ops *so,
		       unsigned char const *data, int no_data)
{
	int i;

	for (i = 0; i < no_data; i++)
		write_reg(sohandle, so, 1, data[i]);
}