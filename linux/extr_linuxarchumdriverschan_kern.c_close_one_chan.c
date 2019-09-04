#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct chan {int fd; scalar_t__ opened; int /*<<< orphan*/  data; TYPE_3__* ops; scalar_t__ enabled; TYPE_2__* line; scalar_t__ output; scalar_t__ input; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  write_irq; int /*<<< orphan*/  read_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  um_free_irq (int /*<<< orphan*/ ,struct chan*) ; 

__attribute__((used)) static void close_one_chan(struct chan *chan, int delay_free_irq)
{
	if (!chan->opened)
		return;

    /* we can safely call free now - it will be marked
     *  as free and freed once the IRQ stopped processing
     */
	if (chan->input && chan->enabled)
		um_free_irq(chan->line->driver->read_irq, chan);
	if (chan->output && chan->enabled)
		um_free_irq(chan->line->driver->write_irq, chan);
	chan->enabled = 0;
	if (chan->ops->close != NULL)
		(*chan->ops->close)(chan->fd, chan->data);

	chan->opened = 0;
	chan->fd = -1;
}