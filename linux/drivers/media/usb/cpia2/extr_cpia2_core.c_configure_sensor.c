#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sensor_flags; } ;
struct TYPE_4__ {TYPE_1__ version; } ;
struct camera_data {TYPE_2__ params; } ;

/* Variables and functions */
#define  CPIA2_VP_SENSOR_FLAGS_404 132 
#define  CPIA2_VP_SENSOR_FLAGS_407 131 
#define  CPIA2_VP_SENSOR_FLAGS_409 130 
#define  CPIA2_VP_SENSOR_FLAGS_410 129 
#define  CPIA2_VP_SENSOR_FLAGS_500 128 
 int EINVAL ; 
 int config_sensor_410 (struct camera_data*,int,int) ; 
 int config_sensor_500 (struct camera_data*,int,int) ; 

__attribute__((used)) static int configure_sensor(struct camera_data *cam,
			    int req_width, int req_height)
{
	int retval;

	switch (cam->params.version.sensor_flags) {
	case CPIA2_VP_SENSOR_FLAGS_404:
	case CPIA2_VP_SENSOR_FLAGS_407:
	case CPIA2_VP_SENSOR_FLAGS_409:
	case CPIA2_VP_SENSOR_FLAGS_410:
		retval = config_sensor_410(cam, req_width, req_height);
		break;
	case CPIA2_VP_SENSOR_FLAGS_500:
		retval = config_sensor_500(cam, req_width, req_height);
		break;
	default:
		return -EINVAL;
	}

	return retval;
}