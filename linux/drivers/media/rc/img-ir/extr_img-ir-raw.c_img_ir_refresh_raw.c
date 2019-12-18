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
typedef  int u32 ;
struct rc_dev {int dummy; } ;
struct img_ir_priv_raw {int last_status; struct rc_dev* rdev; } ;
struct img_ir_priv {struct img_ir_priv_raw raw; } ;

/* Variables and functions */
 int IMG_IR_IRQ_EDGE ; 
 int IMG_IR_IRRXD ; 
 int /*<<< orphan*/  IMG_IR_STATUS ; 
 int img_ir_read (struct img_ir_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_handle (struct rc_dev*) ; 
 int /*<<< orphan*/  ir_raw_event_store_edge (struct rc_dev*,int) ; 

__attribute__((used)) static void img_ir_refresh_raw(struct img_ir_priv *priv, u32 irq_status)
{
	struct img_ir_priv_raw *raw = &priv->raw;
	struct rc_dev *rc_dev = priv->raw.rdev;
	int multiple;
	u32 ir_status;

	/* find whether both rise and fall was detected */
	multiple = ((irq_status & IMG_IR_IRQ_EDGE) == IMG_IR_IRQ_EDGE);
	/*
	 * If so, we need to see if the level has actually changed.
	 * If it's just noise that we didn't have time to process,
	 * there's no point reporting it.
	 */
	ir_status = img_ir_read(priv, IMG_IR_STATUS) & IMG_IR_IRRXD;
	if (multiple && ir_status == raw->last_status)
		return;
	raw->last_status = ir_status;

	/* report the edge to the IR raw decoders */
	if (ir_status) /* low */
		ir_raw_event_store_edge(rc_dev, false);
	else /* high */
		ir_raw_event_store_edge(rc_dev, true);
	ir_raw_event_handle(rc_dev);
}