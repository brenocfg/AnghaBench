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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct surface3_ts_data_finger {int status; } ;
struct surface3_ts_data {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  surface3_spi_report_touch (struct surface3_ts_data*,struct surface3_ts_data_finger*) ; 

__attribute__((used)) static void surface3_spi_process_touch(struct surface3_ts_data *ts_data, u8 *data)
{
	u16 timestamp;
	unsigned int i;
	timestamp = get_unaligned_le16(&data[15]);

	for (i = 0; i < 13; i++) {
		struct surface3_ts_data_finger *finger;

		finger = (struct surface3_ts_data_finger *)&data[17 +
				i * sizeof(struct surface3_ts_data_finger)];

		/*
		 * When bit 5 of status is 1, it marks the end of the report:
		 * - touch present: 0xe7
		 * - touch released: 0xe4
		 * - nothing valuable: 0xff
		 */
		if (finger->status & 0x10)
			break;

		surface3_spi_report_touch(ts_data, finger);
	}

	input_mt_sync_frame(ts_data->input_dev);
	input_sync(ts_data->input_dev);
}