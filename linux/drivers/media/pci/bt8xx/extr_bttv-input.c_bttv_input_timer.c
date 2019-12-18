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
struct timer_list {int dummy; } ;
struct bttv_ir {int /*<<< orphan*/  polling; int /*<<< orphan*/  timer; struct bttv* btv; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct bttv {TYPE_1__ c; } ;

/* Variables and functions */
 scalar_t__ BTTV_BOARD_ENLTV_FM_2 ; 
 struct bttv_ir* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct bttv_ir* ir ; 
 int /*<<< orphan*/  ir_enltv_handle_key (struct bttv*) ; 
 int /*<<< orphan*/  ir_handle_key (struct bttv*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void bttv_input_timer(struct timer_list *t)
{
	struct bttv_ir *ir = from_timer(ir, t, timer);
	struct bttv *btv = ir->btv;

	if (btv->c.type == BTTV_BOARD_ENLTV_FM_2)
		ir_enltv_handle_key(btv);
	else
		ir_handle_key(btv);
	mod_timer(&ir->timer, jiffies + msecs_to_jiffies(ir->polling));
}