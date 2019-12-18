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
struct bttv_buffer_set {TYPE_2__* bottom; TYPE_1__* top; } ;
struct bttv {int loop_irq; scalar_t__ new_input; int /*<<< orphan*/  s_lock; struct bttv_buffer_set curr; int /*<<< orphan*/  framedrop; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  bottom; } ;
struct TYPE_3__ {int /*<<< orphan*/  top; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_RISC_COUNT ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  btread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_buffer_activate_video (struct bttv*,struct bttv_buffer_set*) ; 
 int /*<<< orphan*/  bttv_irq_debug_low_latency (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_irq_next_video (struct bttv*,struct bttv_buffer_set*) ; 
 int /*<<< orphan*/  bttv_irq_wakeup_video (struct bttv*,struct bttv_buffer_set*,struct bttv_buffer_set*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_set_dma (struct bttv*,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_latency ; 
 scalar_t__ is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_mux (struct bttv*,scalar_t__) ; 

__attribute__((used)) static void
bttv_irq_switch_video(struct bttv *btv)
{
	struct bttv_buffer_set new;
	struct bttv_buffer_set old;
	dma_addr_t rc;

	spin_lock(&btv->s_lock);

	/* new buffer set */
	bttv_irq_next_video(btv, &new);
	rc = btread(BT848_RISC_COUNT);
	if ((btv->curr.top    && is_active(&btv->curr.top->top,       rc)) ||
	    (btv->curr.bottom && is_active(&btv->curr.bottom->bottom, rc))) {
		btv->framedrop++;
		if (debug_latency)
			bttv_irq_debug_low_latency(btv, rc);
		spin_unlock(&btv->s_lock);
		return;
	}

	/* switch over */
	old = btv->curr;
	btv->curr = new;
	btv->loop_irq &= ~1;
	bttv_buffer_activate_video(btv, &new);
	bttv_set_dma(btv, 0);

	/* switch input */
	if (UNSET != btv->new_input) {
		video_mux(btv,btv->new_input);
		btv->new_input = UNSET;
	}

	/* wake up finished buffers */
	bttv_irq_wakeup_video(btv, &old, &new, VIDEOBUF_DONE);
	spin_unlock(&btv->s_lock);
}