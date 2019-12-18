#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct most_interface {TYPE_1__* p; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer_size; } ;
struct TYPE_7__ {scalar_t__ num_buffers; struct core_component* comp; scalar_t__ refs; } ;
struct TYPE_6__ {scalar_t__ num_buffers; struct core_component* comp; scalar_t__ refs; } ;
struct most_channel {TYPE_4__ cfg; int /*<<< orphan*/  fifo_lock; int /*<<< orphan*/  fifo; TYPE_3__ pipe1; TYPE_2__ pipe0; } ;
struct mbo {int* num_buffers_ptr; int /*<<< orphan*/  buffer_length; } ;
struct core_component {int dummy; } ;
struct TYPE_5__ {struct most_channel** channel; } ;

/* Variables and functions */
 int dummy_num_buffers ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct mbo* list_pop_mbo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

struct mbo *most_get_mbo(struct most_interface *iface, int id,
			 struct core_component *comp)
{
	struct mbo *mbo;
	struct most_channel *c;
	unsigned long flags;
	int *num_buffers_ptr;

	c = iface->p->channel[id];
	if (unlikely(!c))
		return NULL;

	if (c->pipe0.refs && c->pipe1.refs &&
	    ((comp == c->pipe0.comp && c->pipe0.num_buffers <= 0) ||
	     (comp == c->pipe1.comp && c->pipe1.num_buffers <= 0)))
		return NULL;

	if (comp == c->pipe0.comp)
		num_buffers_ptr = &c->pipe0.num_buffers;
	else if (comp == c->pipe1.comp)
		num_buffers_ptr = &c->pipe1.num_buffers;
	else
		num_buffers_ptr = &dummy_num_buffers;

	spin_lock_irqsave(&c->fifo_lock, flags);
	if (list_empty(&c->fifo)) {
		spin_unlock_irqrestore(&c->fifo_lock, flags);
		return NULL;
	}
	mbo = list_pop_mbo(&c->fifo);
	--*num_buffers_ptr;
	spin_unlock_irqrestore(&c->fifo_lock, flags);

	mbo->num_buffers_ptr = num_buffers_ptr;
	mbo->buffer_length = c->cfg.buffer_size;
	return mbo;
}