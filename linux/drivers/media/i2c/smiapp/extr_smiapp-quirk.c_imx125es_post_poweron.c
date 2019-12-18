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
struct smiapp_sensor {int dummy; } ;
struct smiapp_reg_8 {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct smiapp_reg_8 const*) ; 
 int smiapp_write_8s (struct smiapp_sensor*,struct smiapp_reg_8 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx125es_post_poweron(struct smiapp_sensor *sensor)
{
	/* Taken from v02. No idea what the other two are. */
	static const struct smiapp_reg_8 regs[] = {
		/*
		 * 0x3302: clk during frame blanking:
		 * 0x00 - HS mode, 0x01 - LP11
		 */
		{ 0x3302, 0x01 },
		{ 0x302d, 0x00 },
		{ 0x3b08, 0x8c },
	};

	return smiapp_write_8s(sensor, regs, ARRAY_SIZE(regs));
}