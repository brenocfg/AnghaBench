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
struct gb_uart_serial_flush_request {int /*<<< orphan*/  flags; } ;
struct gb_tty {int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_UART_TYPE_FLUSH_FIFOS ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_uart_serial_flush_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_uart_flush(struct gb_tty *gb_tty, u8 flags)
{
	struct gb_uart_serial_flush_request request;

	request.flags = flags;
	return gb_operation_sync(gb_tty->connection, GB_UART_TYPE_FLUSH_FIFOS,
				 &request, sizeof(request), NULL, 0);
}