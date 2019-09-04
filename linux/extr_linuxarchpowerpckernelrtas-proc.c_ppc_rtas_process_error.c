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

/* Variables and functions */
#define  SENSOR_BUSY 137 
#define  SENSOR_CRITICAL_HIGH 136 
#define  SENSOR_CRITICAL_LOW 135 
#define  SENSOR_DR_ENTITY 134 
#define  SENSOR_HW_ERROR 133 
#define  SENSOR_NORMAL 132 
#define  SENSOR_NOT_EXIST 131 
#define  SENSOR_SUCCESS 130 
#define  SENSOR_WARNING_HIGH 129 
#define  SENSOR_WARNING_LOW 128 

__attribute__((used)) static char *ppc_rtas_process_error(int error)
{
	switch (error) {
		case SENSOR_CRITICAL_HIGH:
			return "(critical high)";
		case SENSOR_WARNING_HIGH:
			return "(warning high)";
		case SENSOR_NORMAL:
			return "(normal)";
		case SENSOR_WARNING_LOW:
			return "(warning low)";
		case SENSOR_CRITICAL_LOW:
			return "(critical low)";
		case SENSOR_SUCCESS:
			return "(read ok)";
		case SENSOR_HW_ERROR:
			return "(hardware error)";
		case SENSOR_BUSY:
			return "(busy)";
		case SENSOR_NOT_EXIST:
			return "(non existent)";
		case SENSOR_DR_ENTITY:
			return "(dr entity removed)";
		default:
			return "(UNKNOWN)";
	}
}