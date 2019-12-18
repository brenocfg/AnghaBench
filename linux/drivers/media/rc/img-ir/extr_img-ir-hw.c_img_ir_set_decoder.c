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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ mask; scalar_t__ data; } ;
struct rc_dev {int /*<<< orphan*/  wakeup_protocol; TYPE_1__ scancode_wakeup_filter; } ;
struct TYPE_4__ {int ctrl; int /*<<< orphan*/  timings; } ;
struct img_ir_priv_hw {int stopping; TYPE_2__ reg_timings; int /*<<< orphan*/  clk_hz; scalar_t__ enabled_protocols; struct img_ir_decoder const* decoder; int /*<<< orphan*/  mode; int /*<<< orphan*/  suspend_timer; int /*<<< orphan*/  end_timer; struct rc_dev* rdev; } ;
struct img_ir_priv {int /*<<< orphan*/  lock; struct img_ir_priv_hw hw; } ;
struct img_ir_decoder {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_CONTROL ; 
 int /*<<< orphan*/  IMG_IR_DATA_LW ; 
 int /*<<< orphan*/  IMG_IR_DATA_UP ; 
 int IMG_IR_IRQ_ALL ; 
 int /*<<< orphan*/  IMG_IR_IRQ_CLEAR ; 
 int IMG_IR_IRQ_EDGE ; 
 int /*<<< orphan*/  IMG_IR_IRQ_ENABLE ; 
 int /*<<< orphan*/  IMG_IR_M_NORMAL ; 
 int IMG_IR_RXDVAL ; 
 int IMG_IR_RXDVALD2 ; 
 int /*<<< orphan*/  IMG_IR_STATUS ; 
 int /*<<< orphan*/  RC_FILTER_NORMAL ; 
 int /*<<< orphan*/  RC_PROTO_UNKNOWN ; 
 int /*<<< orphan*/  _img_ir_set_filter (struct img_ir_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _img_ir_set_wake_filter (struct img_ir_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_ir_decoder_convert (struct img_ir_decoder const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int img_ir_read (struct img_ir_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  img_ir_write_timings (struct img_ir_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void img_ir_set_decoder(struct img_ir_priv *priv,
			       const struct img_ir_decoder *decoder,
			       u64 proto)
{
	struct img_ir_priv_hw *hw = &priv->hw;
	struct rc_dev *rdev = hw->rdev;
	u32 ir_status, irq_en;
	spin_lock_irq(&priv->lock);

	/*
	 * First record that the protocol is being stopped so that the end timer
	 * isn't restarted while we're trying to stop it.
	 */
	hw->stopping = true;

	/*
	 * Release the lock to stop the end timer, since the end timer handler
	 * acquires the lock and we don't want to deadlock waiting for it.
	 */
	spin_unlock_irq(&priv->lock);
	del_timer_sync(&hw->end_timer);
	del_timer_sync(&hw->suspend_timer);
	spin_lock_irq(&priv->lock);

	hw->stopping = false;

	/* switch off and disable interrupts */
	img_ir_write(priv, IMG_IR_CONTROL, 0);
	irq_en = img_ir_read(priv, IMG_IR_IRQ_ENABLE);
	img_ir_write(priv, IMG_IR_IRQ_ENABLE, irq_en & IMG_IR_IRQ_EDGE);
	img_ir_write(priv, IMG_IR_IRQ_CLEAR, IMG_IR_IRQ_ALL & ~IMG_IR_IRQ_EDGE);

	/* ack any data already detected */
	ir_status = img_ir_read(priv, IMG_IR_STATUS);
	if (ir_status & (IMG_IR_RXDVAL | IMG_IR_RXDVALD2)) {
		ir_status &= ~(IMG_IR_RXDVAL | IMG_IR_RXDVALD2);
		img_ir_write(priv, IMG_IR_STATUS, ir_status);
	}

	/* always read data to clear buffer if IR wakes the device */
	img_ir_read(priv, IMG_IR_DATA_LW);
	img_ir_read(priv, IMG_IR_DATA_UP);

	/* switch back to normal mode */
	hw->mode = IMG_IR_M_NORMAL;

	/* clear the wakeup scancode filter */
	rdev->scancode_wakeup_filter.data = 0;
	rdev->scancode_wakeup_filter.mask = 0;
	rdev->wakeup_protocol = RC_PROTO_UNKNOWN;

	/* clear raw filters */
	_img_ir_set_filter(priv, NULL);
	_img_ir_set_wake_filter(priv, NULL);

	/* clear the enabled protocols */
	hw->enabled_protocols = 0;

	/* switch decoder */
	hw->decoder = decoder;
	if (!decoder)
		goto unlock;

	/* set the enabled protocols */
	if (!proto)
		proto = decoder->type;
	hw->enabled_protocols = proto;

	/* write the new timings */
	img_ir_decoder_convert(decoder, &hw->reg_timings, hw->clk_hz);
	img_ir_write_timings(priv, &hw->reg_timings.timings, RC_FILTER_NORMAL);

	/* set up and enable */
	img_ir_write(priv, IMG_IR_CONTROL, hw->reg_timings.ctrl);


unlock:
	spin_unlock_irq(&priv->lock);
}