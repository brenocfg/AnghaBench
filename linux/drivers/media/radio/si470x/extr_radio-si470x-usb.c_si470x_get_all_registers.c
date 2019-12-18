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
struct si470x_device {int /*<<< orphan*/ * usb_buf; int /*<<< orphan*/ * registers; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENTIRE_REPORT ; 
 int /*<<< orphan*/  ENTIRE_REPORT_SIZE ; 
 unsigned char RADIO_REGISTER_NUM ; 
 unsigned char RADIO_REGISTER_SIZE ; 
 int /*<<< orphan*/  get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int si470x_get_report (struct si470x_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si470x_get_all_registers(struct si470x_device *radio)
{
	int retval;
	unsigned char regnr;

	radio->usb_buf[0] = ENTIRE_REPORT;

	retval = si470x_get_report(radio, radio->usb_buf, ENTIRE_REPORT_SIZE);

	if (retval >= 0)
		for (regnr = 0; regnr < RADIO_REGISTER_NUM; regnr++)
			radio->registers[regnr] = get_unaligned_be16(
				&radio->usb_buf[regnr * RADIO_REGISTER_SIZE + 1]);

	return (retval < 0) ? -EINVAL : 0;
}