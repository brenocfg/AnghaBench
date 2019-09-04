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
struct cros_ec_accel_legacy_state {int sensor_num; int /*<<< orphan*/ * sign; int /*<<< orphan*/  ec; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ EC_MEMMAP_ACC_DATA ; 
 int MAX_AXIS ; 
 int bitmap_weight (unsigned long*,int) ; 
 int /*<<< orphan*/  ec_cmd_read_u16 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int find_next_bit (unsigned long*,int,int) ; 

__attribute__((used)) static void read_ec_accel_data_unsafe(struct cros_ec_accel_legacy_state *st,
				      unsigned long scan_mask, s16 *data)
{
	int i = 0;
	int num_enabled = bitmap_weight(&scan_mask, MAX_AXIS);

	/* Read all sensors enabled in scan_mask. Each value is 2 bytes. */
	while (num_enabled--) {
		i = find_next_bit(&scan_mask, MAX_AXIS, i);
		ec_cmd_read_u16(st->ec,
				EC_MEMMAP_ACC_DATA +
				sizeof(s16) *
				(1 + i + st->sensor_num * MAX_AXIS),
				data);
		*data *= st->sign[i];
		i++;
		data++;
	}
}