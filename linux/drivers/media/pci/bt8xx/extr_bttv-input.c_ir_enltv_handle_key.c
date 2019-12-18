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
struct bttv_ir {int mask_keyup; int last_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  mask_keycode; } ;
struct bttv {int /*<<< orphan*/  c; struct bttv_ir* remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_PROTO_UNKNOWN ; 
 int bttv_gpio_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,char*) ; 
 int ir_extract_bits (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keydown_notimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keyup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ir_enltv_handle_key(struct bttv *btv)
{
	struct bttv_ir *ir = btv->remote;
	u32 gpio, data, keyup;

	/* read gpio value */
	gpio = bttv_gpio_read(&btv->c);

	/* extract data */
	data = ir_extract_bits(gpio, ir->mask_keycode);

	/* Check if it is keyup */
	keyup = (gpio & ir->mask_keyup) ? 1UL << 31 : 0;

	if ((ir->last_gpio & 0x7f) != data) {
		dprintk("gpio=0x%x code=%d | %s\n",
			gpio, data,
			(gpio & ir->mask_keyup) ? " up" : "up/down");

		rc_keydown_notimeout(ir->dev, RC_PROTO_UNKNOWN, data, 0);
		if (keyup)
			rc_keyup(ir->dev);
	} else {
		if ((ir->last_gpio & 1UL << 31) == keyup)
			return;

		dprintk("(cnt) gpio=0x%x code=%d | %s\n",
			gpio, data,
			(gpio & ir->mask_keyup) ? " up" : "down");

		if (keyup)
			rc_keyup(ir->dev);
		else
			rc_keydown_notimeout(ir->dev, RC_PROTO_UNKNOWN, data,
					     0);
	}

	ir->last_gpio = data | keyup;
}