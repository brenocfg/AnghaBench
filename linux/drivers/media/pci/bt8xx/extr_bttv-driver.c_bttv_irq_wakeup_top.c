#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  done; int /*<<< orphan*/  state; int /*<<< orphan*/  field_count; int /*<<< orphan*/  ts; } ;
struct bttv_buffer {TYPE_1__ vb; } ;
struct TYPE_4__ {struct bttv_buffer* top; scalar_t__ top_irq; } ;
struct bttv {int /*<<< orphan*/  s_lock; int /*<<< orphan*/  field_count; TYPE_2__ curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RISC_SLOT_O_FIELD ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  bttv_risc_hook (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bttv_irq_wakeup_top(struct bttv *btv)
{
	struct bttv_buffer *wakeup = btv->curr.top;

	if (NULL == wakeup)
		return;

	spin_lock(&btv->s_lock);
	btv->curr.top_irq = 0;
	btv->curr.top = NULL;
	bttv_risc_hook(btv, RISC_SLOT_O_FIELD, NULL, 0);

	wakeup->vb.ts = ktime_get_ns();
	wakeup->vb.field_count = btv->field_count;
	wakeup->vb.state = VIDEOBUF_DONE;
	wake_up(&wakeup->vb.done);
	spin_unlock(&btv->s_lock);
}