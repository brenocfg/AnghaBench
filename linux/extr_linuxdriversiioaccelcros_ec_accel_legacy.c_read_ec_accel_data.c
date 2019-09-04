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
typedef  int u8 ;
struct cros_ec_accel_legacy_state {int /*<<< orphan*/  ec; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  EC_MEMMAP_ACC_STATUS ; 
 int EC_MEMMAP_ACC_STATUS_BUSY_BIT ; 
 int EC_MEMMAP_ACC_STATUS_SAMPLE_ID_MASK ; 
 int EIO ; 
 int /*<<< orphan*/  ec_cmd_read_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  read_ec_accel_data_unsafe (struct cros_ec_accel_legacy_state*,unsigned long,int /*<<< orphan*/ *) ; 
 int read_ec_until_not_busy (struct cros_ec_accel_legacy_state*) ; 

__attribute__((used)) static int read_ec_accel_data(struct cros_ec_accel_legacy_state *st,
			      unsigned long scan_mask, s16 *data)
{
	u8 samp_id = 0xff;
	u8 status = 0;
	int ret;
	int attempts = 0;

	/*
	 * Continually read all data from EC until the status byte after
	 * all reads reflects that the EC is not busy and the sample id
	 * matches the sample id from before all reads. This guarantees
	 * that data read in was not modified by the EC while reading.
	 */
	while ((status & (EC_MEMMAP_ACC_STATUS_BUSY_BIT |
			  EC_MEMMAP_ACC_STATUS_SAMPLE_ID_MASK)) != samp_id) {
		/* If we have tried to read too many times, return error. */
		if (attempts++ >= 5)
			return -EIO;

		/* Read status byte until EC is not busy. */
		ret = read_ec_until_not_busy(st);
		if (ret < 0)
			return ret;
		status = ret;

		/*
		 * Store the current sample id so that we can compare to the
		 * sample id after reading the data.
		 */
		samp_id = status & EC_MEMMAP_ACC_STATUS_SAMPLE_ID_MASK;

		/* Read all EC data, format it, and store it into data. */
		read_ec_accel_data_unsafe(st, scan_mask, data);

		/* Read status byte. */
		ec_cmd_read_u8(st->ec, EC_MEMMAP_ACC_STATUS, &status);
	}

	return 0;
}