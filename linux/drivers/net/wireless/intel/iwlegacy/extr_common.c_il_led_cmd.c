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
struct il_priv {unsigned long blink_on; unsigned long blink_off; TYPE_2__* ops; TYPE_1__* cfg; int /*<<< orphan*/  status; } ;
struct il_led_cmd {void* off; void* on; int /*<<< orphan*/  interval; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int (* send_led_cmd ) (struct il_priv*,struct il_led_cmd*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  led_compensation; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_LED (char*,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  IL_DEF_LED_INTRVL ; 
 int /*<<< orphan*/  IL_LED_LINK ; 
 unsigned long IL_LED_SOLID ; 
 int /*<<< orphan*/  S_READY ; 
 void* il_blink_compensation (struct il_priv*,unsigned long,int /*<<< orphan*/ ) ; 
 int stub1 (struct il_priv*,struct il_led_cmd*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il_led_cmd(struct il_priv *il, unsigned long on, unsigned long off)
{
	struct il_led_cmd led_cmd = {
		.id = IL_LED_LINK,
		.interval = IL_DEF_LED_INTRVL
	};
	int ret;

	if (!test_bit(S_READY, &il->status))
		return -EBUSY;

	if (il->blink_on == on && il->blink_off == off)
		return 0;

	if (off == 0) {
		/* led is SOLID_ON */
		on = IL_LED_SOLID;
	}

	D_LED("Led blink time compensation=%u\n",
	      il->cfg->led_compensation);
	led_cmd.on =
	    il_blink_compensation(il, on,
				  il->cfg->led_compensation);
	led_cmd.off =
	    il_blink_compensation(il, off,
				  il->cfg->led_compensation);

	ret = il->ops->send_led_cmd(il, &led_cmd);
	if (!ret) {
		il->blink_on = on;
		il->blink_off = off;
	}
	return ret;
}