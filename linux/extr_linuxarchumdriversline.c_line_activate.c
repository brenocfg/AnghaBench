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
struct TYPE_2__ {int /*<<< orphan*/  ws_col; int /*<<< orphan*/  ws_row; } ;
struct tty_struct {TYPE_1__ winsize; struct line* driver_data; } ;
struct tty_port {int dummy; } ;
struct line {int sigio; int /*<<< orphan*/  chan_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_enable_winch (int /*<<< orphan*/ ,struct tty_port*) ; 
 int /*<<< orphan*/  chan_window_size (struct line*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int enable_chan (struct line*) ; 

__attribute__((used)) static int line_activate(struct tty_port *port, struct tty_struct *tty)
{
	int ret;
	struct line *line = tty->driver_data;

	ret = enable_chan(line);
	if (ret)
		return ret;

	if (!line->sigio) {
		chan_enable_winch(line->chan_out, port);
		line->sigio = 1;
	}

	chan_window_size(line, &tty->winsize.ws_row,
		&tty->winsize.ws_col);

	return 0;
}