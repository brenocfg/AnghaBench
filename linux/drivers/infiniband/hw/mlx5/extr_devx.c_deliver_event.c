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
struct mlx5_eqe {int dummy; } ;
struct devx_event_subscription {int /*<<< orphan*/  cookie; int /*<<< orphan*/  event_list; struct devx_async_event_file* ev_file; } ;
struct devx_async_event_file {int is_overflow_err; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  event_list; scalar_t__ omit_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  out_data; int /*<<< orphan*/  cookie; } ;
struct devx_async_event_data {int /*<<< orphan*/  list; TYPE_1__ hdr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct devx_async_event_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int deliver_event(struct devx_event_subscription *event_sub,
			 const void *data)
{
	struct devx_async_event_file *ev_file;
	struct devx_async_event_data *event_data;
	unsigned long flags;

	ev_file = event_sub->ev_file;

	if (ev_file->omit_data) {
		spin_lock_irqsave(&ev_file->lock, flags);
		if (!list_empty(&event_sub->event_list)) {
			spin_unlock_irqrestore(&ev_file->lock, flags);
			return 0;
		}

		list_add_tail(&event_sub->event_list, &ev_file->event_list);
		spin_unlock_irqrestore(&ev_file->lock, flags);
		wake_up_interruptible(&ev_file->poll_wait);
		return 0;
	}

	event_data = kzalloc(sizeof(*event_data) + sizeof(struct mlx5_eqe),
			     GFP_ATOMIC);
	if (!event_data) {
		spin_lock_irqsave(&ev_file->lock, flags);
		ev_file->is_overflow_err = 1;
		spin_unlock_irqrestore(&ev_file->lock, flags);
		return -ENOMEM;
	}

	event_data->hdr.cookie = event_sub->cookie;
	memcpy(event_data->hdr.out_data, data, sizeof(struct mlx5_eqe));

	spin_lock_irqsave(&ev_file->lock, flags);
	list_add_tail(&event_data->list, &ev_file->event_list);
	spin_unlock_irqrestore(&ev_file->lock, flags);
	wake_up_interruptible(&ev_file->poll_wait);

	return 0;
}