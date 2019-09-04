#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct param_sensor_framerate {int dummy; } ;
struct fimc_is {size_t config_index; TYPE_5__* config; TYPE_3__* is_p_region; } ;
struct TYPE_9__ {struct param_sensor_framerate frame_rate; } ;
struct TYPE_10__ {TYPE_4__ sensor; } ;
struct TYPE_6__ {struct param_sensor_framerate frame_rate; } ;
struct TYPE_7__ {TYPE_1__ sensor; } ;
struct TYPE_8__ {TYPE_2__ parameter; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hw_param_copy (struct param_sensor_framerate*,struct param_sensor_framerate*) ; 

__attribute__((used)) static void __fimc_is_hw_update_param_sensor_framerate(struct fimc_is *is)
{
	struct param_sensor_framerate *dst, *src;

	dst = &is->is_p_region->parameter.sensor.frame_rate;
	src = &is->config[is->config_index].sensor.frame_rate;
	__hw_param_copy(dst, src);
}