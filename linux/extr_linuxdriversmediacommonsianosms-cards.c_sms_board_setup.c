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
struct sms_board {int /*<<< orphan*/  lna_ctrl; int /*<<< orphan*/  led_lo; int /*<<< orphan*/  led_hi; int /*<<< orphan*/  led_power; } ;

/* Variables and functions */
#define  SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD 130 
#define  SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2 129 
#define  SMS1XXX_BOARD_HAUPPAUGE_WINDHAM 128 
 struct sms_board* sms_get_board (int) ; 
 int /*<<< orphan*/  sms_set_gpio (struct smscore_device_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smscore_get_board_id (struct smscore_device_t*) ; 

int sms_board_setup(struct smscore_device_t *coredev)
{
	int board_id = smscore_get_board_id(coredev);
	struct sms_board *board = sms_get_board(board_id);

	switch (board_id) {
	case SMS1XXX_BOARD_HAUPPAUGE_WINDHAM:
		/* turn off all LEDs */
		sms_set_gpio(coredev, board->led_power, 0);
		sms_set_gpio(coredev, board->led_hi, 0);
		sms_set_gpio(coredev, board->led_lo, 0);
		break;
	case SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2:
	case SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD:
		/* turn off LNA */
		sms_set_gpio(coredev, board->lna_ctrl, 0);
		break;
	}
	return 0;
}