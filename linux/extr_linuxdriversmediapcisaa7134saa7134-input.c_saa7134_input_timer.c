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
struct saa7134_dev {int dummy; } ;
struct saa7134_card_ir {int /*<<< orphan*/  polling; int /*<<< orphan*/  timer; TYPE_1__* dev; } ;
struct TYPE_2__ {struct saa7134_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_key (struct saa7134_dev*) ; 
 struct saa7134_card_ir* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct saa7134_card_ir* ir ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void saa7134_input_timer(struct timer_list *t)
{
	struct saa7134_card_ir *ir = from_timer(ir, t, timer);
	struct saa7134_dev *dev = ir->dev->priv;

	build_key(dev);
	mod_timer(&ir->timer, jiffies + msecs_to_jiffies(ir->polling));
}