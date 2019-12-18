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
struct v4l2_subdev {int dummy; } ;
struct et8ek8_sensor {int dummy; } ;

/* Variables and functions */
 int et8ek8_configure (struct et8ek8_sensor*) ; 
 int et8ek8_stream_off (struct et8ek8_sensor*) ; 
 int et8ek8_stream_on (struct et8ek8_sensor*) ; 
 struct et8ek8_sensor* to_et8ek8_sensor (struct v4l2_subdev*) ; 

__attribute__((used)) static int et8ek8_s_stream(struct v4l2_subdev *subdev, int streaming)
{
	struct et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	int ret;

	if (!streaming)
		return et8ek8_stream_off(sensor);

	ret = et8ek8_configure(sensor);
	if (ret < 0)
		return ret;

	return et8ek8_stream_on(sensor);
}