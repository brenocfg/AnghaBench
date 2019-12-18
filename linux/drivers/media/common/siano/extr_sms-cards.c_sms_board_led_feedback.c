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
struct smscore_device_t {int dummy; } ;
struct sms_board {int /*<<< orphan*/  led_hi; int /*<<< orphan*/  led_lo; } ;

/* Variables and functions */
#define  SMS1XXX_BOARD_HAUPPAUGE_WINDHAM 128 
 int SMS_LED_HI ; 
 int SMS_LED_LO ; 
 struct sms_board* sms_get_board (int) ; 
 int /*<<< orphan*/  sms_set_gpio (struct smscore_device_t*,int /*<<< orphan*/ ,int) ; 
 int smscore_get_board_id (struct smscore_device_t*) ; 
 int smscore_led_state (struct smscore_device_t*,int) ; 

int sms_board_led_feedback(struct smscore_device_t *coredev, int led)
{
	int board_id = smscore_get_board_id(coredev);
	struct sms_board *board = sms_get_board(board_id);

	/* don't touch GPIO if LEDs are already set */
	if (smscore_led_state(coredev, -1) == led)
		return 0;

	switch (board_id) {
	case SMS1XXX_BOARD_HAUPPAUGE_WINDHAM:
		sms_set_gpio(coredev,
			     board->led_lo, (led & SMS_LED_LO) ? 1 : 0);
		sms_set_gpio(coredev,
			     board->led_hi, (led & SMS_LED_HI) ? 1 : 0);

		smscore_led_state(coredev, led);
		break;
	}
	return 0;
}