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
struct rmi_2d_sensor {int nbr_fingers; scalar_t__ report_rel; int /*<<< orphan*/  input; int /*<<< orphan*/ * objs; int /*<<< orphan*/  dmax; int /*<<< orphan*/  tracking_pos; int /*<<< orphan*/  tracking_slots; scalar_t__ kernel_tracking; scalar_t__ report_abs; } ;
struct TYPE_2__ {int* f_state; } ;
struct f11_data {TYPE_1__ data; } ;

/* Variables and functions */
 int F11_RESERVED ; 
 int RMI_F11_ABS_BYTES ; 
 int RMI_F11_REL_BYTES ; 
 int /*<<< orphan*/  input_mt_assign_slots (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  rmi_2d_sensor_abs_report (struct rmi_2d_sensor*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rmi_f11_abs_pos_process (struct f11_data*,struct rmi_2d_sensor*,int /*<<< orphan*/ *,int,int) ; 
 int rmi_f11_parse_finger_state (int const*,int) ; 
 int /*<<< orphan*/  rmi_f11_rel_pos_report (struct f11_data*,int) ; 

__attribute__((used)) static void rmi_f11_finger_handler(struct f11_data *f11,
				   struct rmi_2d_sensor *sensor, int size)
{
	const u8 *f_state = f11->data.f_state;
	u8 finger_state;
	u8 i;
	int abs_fingers;
	int rel_fingers;
	int abs_size = sensor->nbr_fingers * RMI_F11_ABS_BYTES;

	if (sensor->report_abs) {
		if (abs_size > size)
			abs_fingers = size / RMI_F11_ABS_BYTES;
		else
			abs_fingers = sensor->nbr_fingers;

		for (i = 0; i < abs_fingers; i++) {
			/* Possible of having 4 fingers per f_state register */
			finger_state = rmi_f11_parse_finger_state(f_state, i);
			if (finger_state == F11_RESERVED) {
				pr_err("Invalid finger state[%d]: 0x%02x", i,
					finger_state);
				continue;
			}

			rmi_f11_abs_pos_process(f11, sensor, &sensor->objs[i],
							finger_state, i);
		}

		/*
		 * the absolute part is made in 2 parts to allow the kernel
		 * tracking to take place.
		 */
		if (sensor->kernel_tracking)
			input_mt_assign_slots(sensor->input,
					      sensor->tracking_slots,
					      sensor->tracking_pos,
					      sensor->nbr_fingers,
					      sensor->dmax);

		for (i = 0; i < abs_fingers; i++) {
			finger_state = rmi_f11_parse_finger_state(f_state, i);
			if (finger_state == F11_RESERVED)
				/* no need to send twice the error */
				continue;

			rmi_2d_sensor_abs_report(sensor, &sensor->objs[i], i);
		}

		input_mt_sync_frame(sensor->input);
	} else if (sensor->report_rel) {
		if ((abs_size + sensor->nbr_fingers * RMI_F11_REL_BYTES) > size)
			rel_fingers = (size - abs_size) / RMI_F11_REL_BYTES;
		else
			rel_fingers = sensor->nbr_fingers;

		for (i = 0; i < rel_fingers; i++)
			rmi_f11_rel_pos_report(f11, i);
	}

}