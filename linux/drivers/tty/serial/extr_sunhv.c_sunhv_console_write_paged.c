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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ sysrq; } ;
struct console {int dummy; } ;

/* Variables and functions */
 unsigned long HV_EOK ; 
 unsigned long __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_write_page ; 
 unsigned int fill_con_write_page (char const*,unsigned int,unsigned long*) ; 
 scalar_t__ oops_in_progress ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long sun4v_con_write (unsigned long,unsigned long,unsigned long*) ; 
 struct uart_port* sunhv_port ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sunhv_console_write_paged(struct console *con, const char *s, unsigned n)
{
	struct uart_port *port = sunhv_port;
	unsigned long flags;
	int locked = 1;

	if (port->sysrq || oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	else
		spin_lock_irqsave(&port->lock, flags);

	while (n > 0) {
		unsigned long ra = __pa(con_write_page);
		unsigned long page_bytes;
		unsigned int cpy = fill_con_write_page(s, n,
						       &page_bytes);

		n -= cpy;
		s += cpy;
		while (page_bytes > 0) {
			unsigned long written;
			int limit = 1000000;

			while (limit--) {
				unsigned long stat;

				stat = sun4v_con_write(ra, page_bytes,
						       &written);
				if (stat == HV_EOK)
					break;
				udelay(1);
			}
			if (limit < 0)
				break;
			page_bytes -= written;
			ra += written;
		}
	}

	if (locked)
		spin_unlock_irqrestore(&port->lock, flags);
}