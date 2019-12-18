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
struct earlycon_device {int /*<<< orphan*/  port; } ;
struct console {struct earlycon_device* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbi_putc ; 
 int /*<<< orphan*/  uart_console_write (int /*<<< orphan*/ *,char const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sbi_console_write(struct console *con,
			      const char *s, unsigned n)
{
	struct earlycon_device *dev = con->data;
	uart_console_write(&dev->port, s, n, sbi_putc);
}