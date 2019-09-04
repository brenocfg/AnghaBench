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
struct vibra_info {int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_AUDIO_RES_APLL ; 
 int /*<<< orphan*/  TWL4030_AUDIO_RES_POWER ; 
 int /*<<< orphan*/  TWL4030_MODULE_AUDIO_VOICE ; 
 int /*<<< orphan*/  TWL4030_REG_VIBRA_CTL ; 
 int TWL4030_VIBRA_EN ; 
 int /*<<< orphan*/  twl4030_audio_enable_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vibra_enable(struct vibra_info *info)
{
	u8 reg;

	twl4030_audio_enable_resource(TWL4030_AUDIO_RES_POWER);

	/* turn H-Bridge on */
	twl_i2c_read_u8(TWL4030_MODULE_AUDIO_VOICE,
			&reg, TWL4030_REG_VIBRA_CTL);
	twl_i2c_write_u8(TWL4030_MODULE_AUDIO_VOICE,
			 (reg | TWL4030_VIBRA_EN), TWL4030_REG_VIBRA_CTL);

	twl4030_audio_enable_resource(TWL4030_AUDIO_RES_APLL);

	info->enabled = true;
}