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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rpi_touchscreen {int /*<<< orphan*/  dsi; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  mipi_dsi_generic_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int rpi_touchscreen_write(struct rpi_touchscreen *ts, u16 reg, u32 val)
{
	u8 msg[] = {
		reg,
		reg >> 8,
		val,
		val >> 8,
		val >> 16,
		val >> 24,
	};

	mipi_dsi_generic_write(ts->dsi, msg, sizeof(msg));

	return 0;
}