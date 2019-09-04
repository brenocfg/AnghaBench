#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct twl4030_audio {TYPE_1__* resource; } ;
typedef  enum twl4030_audio_res { ____Placeholder_twl4030_audio_res } twl4030_audio_res ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_MODULE_AUDIO_VOICE ; 
 struct twl4030_audio* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_audio_dev ; 
 int /*<<< orphan*/  twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int twl4030_audio_get_resource(enum twl4030_audio_res id)
{
	struct twl4030_audio *audio = platform_get_drvdata(twl4030_audio_dev);
	u8 val;

	twl_i2c_read_u8(TWL4030_MODULE_AUDIO_VOICE, &val,
			audio->resource[id].reg);

	return val;
}