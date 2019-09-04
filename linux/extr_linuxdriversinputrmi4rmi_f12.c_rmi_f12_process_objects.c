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
struct rmi_2d_sensor_abs_object {int x; int y; int z; int wx; int wy; int /*<<< orphan*/  type; int /*<<< orphan*/  mt_tool; } ;
struct rmi_2d_sensor {struct rmi_2d_sensor_abs_object* objs; int /*<<< orphan*/  dmax; int /*<<< orphan*/  nbr_fingers; int /*<<< orphan*/  tracking_pos; int /*<<< orphan*/  tracking_slots; int /*<<< orphan*/  input; scalar_t__ kernel_tracking; } ;
struct f12_data {TYPE_1__* data1; struct rmi_2d_sensor sensor; } ;
struct TYPE_2__ {int num_subpackets; } ;

/* Variables and functions */
 int F12_DATA1_BYTES_PER_OBJ ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  MT_TOOL_PALM ; 
 int /*<<< orphan*/  MT_TOOL_PEN ; 
 int /*<<< orphan*/  RMI_2D_OBJECT_FINGER ; 
 int /*<<< orphan*/  RMI_2D_OBJECT_NONE ; 
 int /*<<< orphan*/  RMI_2D_OBJECT_PALM ; 
 int /*<<< orphan*/  RMI_2D_OBJECT_STYLUS ; 
 int /*<<< orphan*/  RMI_2D_OBJECT_UNCLASSIFIED ; 
#define  RMI_F12_OBJECT_FINGER 131 
#define  RMI_F12_OBJECT_PALM 130 
#define  RMI_F12_OBJECT_STYLUS 129 
#define  RMI_F12_OBJECT_UNCLASSIFIED 128 
 int /*<<< orphan*/  input_mt_assign_slots (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmi_2d_sensor_abs_process (struct rmi_2d_sensor*,struct rmi_2d_sensor_abs_object*,int) ; 
 int /*<<< orphan*/  rmi_2d_sensor_abs_report (struct rmi_2d_sensor*,struct rmi_2d_sensor_abs_object*,int) ; 

__attribute__((used)) static void rmi_f12_process_objects(struct f12_data *f12, u8 *data1, int size)
{
	int i;
	struct rmi_2d_sensor *sensor = &f12->sensor;
	int objects = f12->data1->num_subpackets;

	if ((f12->data1->num_subpackets * F12_DATA1_BYTES_PER_OBJ) > size)
		objects = size / F12_DATA1_BYTES_PER_OBJ;

	for (i = 0; i < objects; i++) {
		struct rmi_2d_sensor_abs_object *obj = &sensor->objs[i];

		obj->type = RMI_2D_OBJECT_NONE;
		obj->mt_tool = MT_TOOL_FINGER;

		switch (data1[0]) {
		case RMI_F12_OBJECT_FINGER:
			obj->type = RMI_2D_OBJECT_FINGER;
			break;
		case RMI_F12_OBJECT_STYLUS:
			obj->type = RMI_2D_OBJECT_STYLUS;
			obj->mt_tool = MT_TOOL_PEN;
			break;
		case RMI_F12_OBJECT_PALM:
			obj->type = RMI_2D_OBJECT_PALM;
			obj->mt_tool = MT_TOOL_PALM;
			break;
		case RMI_F12_OBJECT_UNCLASSIFIED:
			obj->type = RMI_2D_OBJECT_UNCLASSIFIED;
			break;
		}

		obj->x = (data1[2] << 8) | data1[1];
		obj->y = (data1[4] << 8) | data1[3];
		obj->z = data1[5];
		obj->wx = data1[6];
		obj->wy = data1[7];

		rmi_2d_sensor_abs_process(sensor, obj, i);

		data1 += F12_DATA1_BYTES_PER_OBJ;
	}

	if (sensor->kernel_tracking)
		input_mt_assign_slots(sensor->input,
				      sensor->tracking_slots,
				      sensor->tracking_pos,
				      sensor->nbr_fingers,
				      sensor->dmax);

	for (i = 0; i < objects; i++)
		rmi_2d_sensor_abs_report(sensor, &sensor->objs[i], i);
}