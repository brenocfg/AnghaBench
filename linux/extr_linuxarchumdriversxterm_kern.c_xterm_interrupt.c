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
struct xterm_wait {int new_fd; int /*<<< orphan*/  ready; int /*<<< orphan*/  pid; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int os_rcv_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t xterm_interrupt(int irq, void *data)
{
	struct xterm_wait *xterm = data;
	int fd;

	fd = os_rcv_fd(xterm->fd, &xterm->pid);
	if (fd == -EAGAIN)
		return IRQ_NONE;

	xterm->new_fd = fd;
	complete(&xterm->ready);

	return IRQ_HANDLED;
}