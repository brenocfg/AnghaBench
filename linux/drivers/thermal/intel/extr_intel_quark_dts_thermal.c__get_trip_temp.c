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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MBI_REG_READ ; 
 int QRK_DTS_MASK_TP_THRES ; 
 int /*<<< orphan*/  QRK_DTS_REG_OFFSET_PTPS ; 
 int QRK_DTS_SHIFT_TP ; 
 scalar_t__ QRK_DTS_TEMP_BASE ; 
 int /*<<< orphan*/  QRK_MBI_UNIT_RMU ; 
 int /*<<< orphan*/  dts_update_mutex ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _get_trip_temp(int trip, int *temp)
{
	int status;
	u32 out;

	mutex_lock(&dts_update_mutex);
	status = iosf_mbi_read(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			       QRK_DTS_REG_OFFSET_PTPS, &out);
	mutex_unlock(&dts_update_mutex);

	if (status)
		return status;

	/*
	 * Thermal Sensor Programmable Trip Point Register has 8-bit
	 * fields for critical (catastrophic) and hot set trip point
	 * thresholds. The threshold value is always offset by its
	 * temperature base (50 degree Celsius).
	 */
	*temp = (out >> (trip * QRK_DTS_SHIFT_TP)) & QRK_DTS_MASK_TP_THRES;
	*temp -= QRK_DTS_TEMP_BASE;

	return 0;
}