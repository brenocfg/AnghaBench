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
struct rmi_2d_sensor_platform_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

inline int rmi_2d_sensor_of_probe(struct device *dev,
			struct rmi_2d_sensor_platform_data *pdata)
{
	return -ENODEV;
}