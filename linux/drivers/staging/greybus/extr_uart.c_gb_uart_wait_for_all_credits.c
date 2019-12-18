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
struct gb_tty {scalar_t__ credits; TYPE_1__* gbphy_dev; int /*<<< orphan*/  credits_complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GB_UART_CREDIT_WAIT_TIMEOUT_MSEC ; 
 scalar_t__ GB_UART_FIRMWARE_CREDITS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_uart_wait_for_all_credits(struct gb_tty *gb_tty)
{
	int ret;

	if (gb_tty->credits == GB_UART_FIRMWARE_CREDITS)
		return 0;

	ret = wait_for_completion_timeout(&gb_tty->credits_complete,
			msecs_to_jiffies(GB_UART_CREDIT_WAIT_TIMEOUT_MSEC));
	if (!ret) {
		dev_err(&gb_tty->gbphy_dev->dev,
			"time out waiting for credits\n");
		return -ETIMEDOUT;
	}

	return 0;
}