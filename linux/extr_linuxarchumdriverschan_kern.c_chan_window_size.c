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
struct line {struct chan* chan_out; struct chan* chan_in; } ;
struct chan {int /*<<< orphan*/  data; int /*<<< orphan*/  fd; TYPE_1__* ops; scalar_t__ primary; } ;
struct TYPE_2__ {int (* window_size ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short*,unsigned short*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short*,unsigned short*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short*,unsigned short*) ; 

int chan_window_size(struct line *line, unsigned short *rows_out,
		      unsigned short *cols_out)
{
	struct chan *chan;

	chan = line->chan_in;
	if (chan && chan->primary) {
		if (chan->ops->window_size == NULL)
			return 0;
		return chan->ops->window_size(chan->fd, chan->data,
					      rows_out, cols_out);
	}
	chan = line->chan_out;
	if (chan && chan->primary) {
		if (chan->ops->window_size == NULL)
			return 0;
		return chan->ops->window_size(chan->fd, chan->data,
					      rows_out, cols_out);
	}
	return 0;
}