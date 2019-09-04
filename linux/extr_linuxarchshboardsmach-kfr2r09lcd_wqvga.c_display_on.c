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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_memory (void*,struct sh_mobile_lcdc_sys_bus_ops*) ; 
 int /*<<< orphan*/  data_frame_if ; 
 int /*<<< orphan*/  data_gamma ; 
 int /*<<< orphan*/  data_panel ; 
 int /*<<< orphan*/  data_power ; 
 int /*<<< orphan*/  data_timing ; 
 int /*<<< orphan*/  data_timing_src ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  write_data (void*,struct sh_mobile_lcdc_sys_bus_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_memory_start (void*,struct sh_mobile_lcdc_sys_bus_ops*) ; 
 int /*<<< orphan*/  write_reg (void*,struct sh_mobile_lcdc_sys_bus_ops*,int,int) ; 

__attribute__((used)) static void display_on(void *sohandle,
		       struct sh_mobile_lcdc_sys_bus_ops *so)
{
	/* access protect off */
	write_reg(sohandle, so, 0, 0xb0);
	write_reg(sohandle, so, 1, 0x00);

	/* exit deep standby mode */
	write_reg(sohandle, so, 0, 0xb1);
	write_reg(sohandle, so, 1, 0x00);

	/* frame memory I/F */
	write_reg(sohandle, so, 0, 0xb3);
	write_data(sohandle, so, data_frame_if, ARRAY_SIZE(data_frame_if));

	/* display mode and frame memory write mode */
	write_reg(sohandle, so, 0, 0xb4);
	write_reg(sohandle, so, 1, 0x00); /* DBI, internal clock */

	/* panel */
	write_reg(sohandle, so, 0, 0xc0);
	write_data(sohandle, so, data_panel, ARRAY_SIZE(data_panel));

	/* timing (normal) */
	write_reg(sohandle, so, 0, 0xc1);
	write_data(sohandle, so, data_timing, ARRAY_SIZE(data_timing));

	/* timing (partial) */
	write_reg(sohandle, so, 0, 0xc2);
	write_data(sohandle, so, data_timing, ARRAY_SIZE(data_timing));

	/* timing (idle) */
	write_reg(sohandle, so, 0, 0xc3);
	write_data(sohandle, so, data_timing, ARRAY_SIZE(data_timing));

	/* timing (source/VCOM/gate driving) */
	write_reg(sohandle, so, 0, 0xc4);
	write_data(sohandle, so, data_timing_src, ARRAY_SIZE(data_timing_src));

	/* gamma (red) */
	write_reg(sohandle, so, 0, 0xc8);
	write_data(sohandle, so, data_gamma, ARRAY_SIZE(data_gamma));

	/* gamma (green) */
	write_reg(sohandle, so, 0, 0xc9);
	write_data(sohandle, so, data_gamma, ARRAY_SIZE(data_gamma));

	/* gamma (blue) */
	write_reg(sohandle, so, 0, 0xca);
	write_data(sohandle, so, data_gamma, ARRAY_SIZE(data_gamma));

	/* power (common) */
	write_reg(sohandle, so, 0, 0xd0);
	write_data(sohandle, so, data_power, ARRAY_SIZE(data_power));

	/* VCOM */
	write_reg(sohandle, so, 0, 0xd1);
	write_reg(sohandle, so, 1, 0x00);
	write_reg(sohandle, so, 1, 0x0f);
	write_reg(sohandle, so, 1, 0x02);

	/* power (normal) */
	write_reg(sohandle, so, 0, 0xd2);
	write_reg(sohandle, so, 1, 0x63);
	write_reg(sohandle, so, 1, 0x24);

	/* power (partial) */
	write_reg(sohandle, so, 0, 0xd3);
	write_reg(sohandle, so, 1, 0x63);
	write_reg(sohandle, so, 1, 0x24);

	/* power (idle) */
	write_reg(sohandle, so, 0, 0xd4);
	write_reg(sohandle, so, 1, 0x63);
	write_reg(sohandle, so, 1, 0x24);

	write_reg(sohandle, so, 0, 0xd8);
	write_reg(sohandle, so, 1, 0x77);
	write_reg(sohandle, so, 1, 0x77);

	/* TE signal */
	write_reg(sohandle, so, 0, 0x35);
	write_reg(sohandle, so, 1, 0x00);

	/* TE signal line */
	write_reg(sohandle, so, 0, 0x44);
	write_reg(sohandle, so, 1, 0x00);
	write_reg(sohandle, so, 1, 0x00);

	/* column address */
	write_reg(sohandle, so, 0, 0x2a);
	write_reg(sohandle, so, 1, 0x00);
	write_reg(sohandle, so, 1, 0x00);
	write_reg(sohandle, so, 1, 0x00);
	write_reg(sohandle, so, 1, 0xef);

	/* page address */
	write_reg(sohandle, so, 0, 0x2b);
	write_reg(sohandle, so, 1, 0x00);
	write_reg(sohandle, so, 1, 0x00);
	write_reg(sohandle, so, 1, 0x01);
	write_reg(sohandle, so, 1, 0x8f);

	/* exit sleep mode */
	write_reg(sohandle, so, 0, 0x11);

	mdelay(120);

	/* clear vram */
	clear_memory(sohandle, so);

	/* display ON */
	write_reg(sohandle, so, 0, 0x29);
	mdelay(1);

	write_memory_start(sohandle, so);
}