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
typedef  void* u64 ;
struct bttv_buffer_set {TYPE_3__* bottom; TYPE_3__* top; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr; } ;
struct bttv {int /*<<< orphan*/  field_count; TYPE_1__ c; } ;
struct TYPE_5__ {unsigned int state; int /*<<< orphan*/  done; int /*<<< orphan*/  field_count; void* ts; } ;
struct TYPE_6__ {TYPE_2__ vb; } ;

/* Variables and functions */
 int irq_debug ; 
 void* ktime_get_ns () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bttv_irq_wakeup_video(struct bttv *btv, struct bttv_buffer_set *wakeup,
		      struct bttv_buffer_set *curr, unsigned int state)
{
	u64 ts = ktime_get_ns();

	if (wakeup->top == wakeup->bottom) {
		if (NULL != wakeup->top && curr->top != wakeup->top) {
			if (irq_debug > 1)
				pr_debug("%d: wakeup: both=%p\n",
					 btv->c.nr, wakeup->top);
			wakeup->top->vb.ts = ts;
			wakeup->top->vb.field_count = btv->field_count;
			wakeup->top->vb.state = state;
			wake_up(&wakeup->top->vb.done);
		}
	} else {
		if (NULL != wakeup->top && curr->top != wakeup->top) {
			if (irq_debug > 1)
				pr_debug("%d: wakeup: top=%p\n",
					 btv->c.nr, wakeup->top);
			wakeup->top->vb.ts = ts;
			wakeup->top->vb.field_count = btv->field_count;
			wakeup->top->vb.state = state;
			wake_up(&wakeup->top->vb.done);
		}
		if (NULL != wakeup->bottom && curr->bottom != wakeup->bottom) {
			if (irq_debug > 1)
				pr_debug("%d: wakeup: bottom=%p\n",
					 btv->c.nr, wakeup->bottom);
			wakeup->bottom->vb.ts = ts;
			wakeup->bottom->vb.field_count = btv->field_count;
			wakeup->bottom->vb.state = state;
			wake_up(&wakeup->bottom->vb.done);
		}
	}
}