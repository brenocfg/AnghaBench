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
typedef  int u32 ;
struct bttv_ir {int last_gpio; int mask_keydown; int mask_keyup; int /*<<< orphan*/  dev; scalar_t__ polling; int /*<<< orphan*/  mask_keycode; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct bttv {TYPE_1__ c; struct bttv_ir* remote; } ;

/* Variables and functions */
 scalar_t__ BTTV_BOARD_WINFAST2000 ; 
 int /*<<< orphan*/  RC_PROTO_UNKNOWN ; 
 int bttv_gpio_read (TYPE_1__*) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,char*,char*,char*) ; 
 int ir_extract_bits (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keydown_notimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keyup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ir_handle_key(struct bttv *btv)
{
	struct bttv_ir *ir = btv->remote;
	u32 gpio,data;

	/* read gpio value */
	gpio = bttv_gpio_read(&btv->c);
	if (ir->polling) {
		if (ir->last_gpio == gpio)
			return;
		ir->last_gpio = gpio;
	}

	/* extract data */
	data = ir_extract_bits(gpio, ir->mask_keycode);
	dprintk("irq gpio=0x%x code=%d | %s%s%s\n",
		gpio, data,
		ir->polling               ? "poll"  : "irq",
		(gpio & ir->mask_keydown) ? " down" : "",
		(gpio & ir->mask_keyup)   ? " up"   : "");

	if ((ir->mask_keydown && (gpio & ir->mask_keydown)) ||
	    (ir->mask_keyup   && !(gpio & ir->mask_keyup))) {
		rc_keydown_notimeout(ir->dev, RC_PROTO_UNKNOWN, data, 0);
	} else {
		/* HACK: Probably, ir->mask_keydown is missing
		   for this board */
		if (btv->c.type == BTTV_BOARD_WINFAST2000)
			rc_keydown_notimeout(ir->dev, RC_PROTO_UNKNOWN, data,
					     0);

		rc_keyup(ir->dev);
	}
}