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
struct adxl34x_platform_data {int /*<<< orphan*/ * ev_code_tap; } ;
struct adxl34x {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int ADXL_X_AXIS ; 
 int ADXL_Z_AXIS ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adxl34x_send_key_events(struct adxl34x *ac,
		struct adxl34x_platform_data *pdata, int status, int press)
{
	int i;

	for (i = ADXL_X_AXIS; i <= ADXL_Z_AXIS; i++) {
		if (status & (1 << (ADXL_Z_AXIS - i)))
			input_report_key(ac->input,
					 pdata->ev_code_tap[i], press);
	}
}