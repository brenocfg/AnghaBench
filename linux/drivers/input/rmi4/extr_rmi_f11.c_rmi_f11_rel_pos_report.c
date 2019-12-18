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
typedef  size_t u8 ;
struct rmi_2d_sensor {int dummy; } ;
struct f11_2d_data {int /*<<< orphan*/ * rel_pos; } ;
struct f11_data {struct f11_2d_data data; struct rmi_2d_sensor sensor; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 size_t RMI_F11_REL_BYTES ; 
 int /*<<< orphan*/  rmi_2d_sensor_rel_report (struct rmi_2d_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rmi_f11_rel_pos_report(struct f11_data *f11, u8 n_finger)
{
	struct rmi_2d_sensor *sensor = &f11->sensor;
	struct f11_2d_data *data = &f11->data;
	s8 x, y;

	x = data->rel_pos[n_finger * RMI_F11_REL_BYTES];
	y = data->rel_pos[n_finger * RMI_F11_REL_BYTES + 1];

	rmi_2d_sensor_rel_report(sensor, x, y);
}