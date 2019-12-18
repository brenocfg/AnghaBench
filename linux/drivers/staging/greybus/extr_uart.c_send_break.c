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
struct gb_uart_set_break_request {int state; } ;
struct gb_tty {int /*<<< orphan*/  connection; TYPE_1__* gbphy_dev; } ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GB_UART_TYPE_SEND_BREAK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_uart_set_break_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_break(struct gb_tty *gb_tty, u8 state)
{
	struct gb_uart_set_break_request request;

	if ((state != 0) && (state != 1)) {
		dev_err(&gb_tty->gbphy_dev->dev,
			"invalid break state of %d\n", state);
		return -EINVAL;
	}

	request.state = state;
	return gb_operation_sync(gb_tty->connection, GB_UART_TYPE_SEND_BREAK,
				 &request, sizeof(request), NULL, 0);
}