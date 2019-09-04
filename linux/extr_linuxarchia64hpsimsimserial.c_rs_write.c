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
struct tty_struct {int /*<<< orphan*/  stopped; struct serial_state* driver_data; } ;
struct TYPE_2__ {int head; int /*<<< orphan*/  tail; scalar_t__ buf; } ;
struct serial_state {TYPE_1__ xmit; } ;

/* Variables and functions */
 scalar_t__ CIRC_CNT (int,int /*<<< orphan*/ ,int) ; 
 int CIRC_SPACE_TO_END (int,int /*<<< orphan*/ ,int) ; 
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 int /*<<< orphan*/  transmit_chars (struct tty_struct*,struct serial_state*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rs_write(struct tty_struct * tty,
		    const unsigned char *buf, int count)
{
	struct serial_state *info = tty->driver_data;
	int	c, ret = 0;
	unsigned long flags;

	if (!info->xmit.buf)
		return 0;

	local_irq_save(flags);
	while (1) {
		c = CIRC_SPACE_TO_END(info->xmit.head, info->xmit.tail, SERIAL_XMIT_SIZE);
		if (count < c)
			c = count;
		if (c <= 0) {
			break;
		}
		memcpy(info->xmit.buf + info->xmit.head, buf, c);
		info->xmit.head = ((info->xmit.head + c) &
				   (SERIAL_XMIT_SIZE-1));
		buf += c;
		count -= c;
		ret += c;
	}
	local_irq_restore(flags);
	/*
	 * Hey, we transmit directly from here in our case
	 */
	if (CIRC_CNT(info->xmit.head, info->xmit.tail, SERIAL_XMIT_SIZE) &&
			!tty->stopped)
		transmit_chars(tty, info, NULL);

	return ret;
}