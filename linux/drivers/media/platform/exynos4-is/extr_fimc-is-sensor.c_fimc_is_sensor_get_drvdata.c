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
struct sensor_drv_data {int dummy; } ;
struct of_device_id {struct sensor_drv_data const* data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fimc_is_sensor_of_ids ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 

const struct sensor_drv_data *fimc_is_sensor_get_drvdata(
			struct device_node *node)
{
	const struct of_device_id *of_id;

	of_id = of_match_node(fimc_is_sensor_of_ids, node);
	return of_id ? of_id->data : NULL;
}