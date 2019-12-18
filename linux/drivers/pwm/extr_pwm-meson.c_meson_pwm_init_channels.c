#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct clk_init_data* init; } ;
struct TYPE_8__ {TYPE_5__ hw; int /*<<< orphan*/ * table; int /*<<< orphan*/ * lock; scalar_t__ flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  shift; scalar_t__ reg; } ;
struct meson_pwm_channel {int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  clk; TYPE_3__ mux; } ;
struct TYPE_6__ {unsigned int npwm; struct device* dev; } ;
struct meson_pwm {int /*<<< orphan*/  lock; scalar_t__ base; TYPE_2__* data; struct meson_pwm_channel* channels; TYPE_1__ chip; } ;
struct device {int dummy; } ;
struct clk_init_data {char* name; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; scalar_t__ flags; int /*<<< orphan*/ * ops; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_9__ {int /*<<< orphan*/  clk_sel_shift; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISC_CLK_SEL_MASK ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_MISC_AB ; 
 int /*<<< orphan*/  clk_mux_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get_optional (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_register (struct device*,TYPE_5__*) ; 
 TYPE_4__* meson_pwm_per_channel_data ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int meson_pwm_init_channels(struct meson_pwm *meson)
{
	struct device *dev = meson->chip.dev;
	struct clk_init_data init;
	unsigned int i;
	char name[255];
	int err;

	for (i = 0; i < meson->chip.npwm; i++) {
		struct meson_pwm_channel *channel = &meson->channels[i];

		snprintf(name, sizeof(name), "%s#mux%u", dev_name(dev), i);

		init.name = name;
		init.ops = &clk_mux_ops;
		init.flags = 0;
		init.parent_names = meson->data->parent_names;
		init.num_parents = meson->data->num_parents;

		channel->mux.reg = meson->base + REG_MISC_AB;
		channel->mux.shift =
				meson_pwm_per_channel_data[i].clk_sel_shift;
		channel->mux.mask = MISC_CLK_SEL_MASK;
		channel->mux.flags = 0;
		channel->mux.lock = &meson->lock;
		channel->mux.table = NULL;
		channel->mux.hw.init = &init;

		channel->clk = devm_clk_register(dev, &channel->mux.hw);
		if (IS_ERR(channel->clk)) {
			err = PTR_ERR(channel->clk);
			dev_err(dev, "failed to register %s: %d\n", name, err);
			return err;
		}

		snprintf(name, sizeof(name), "clkin%u", i);

		channel->clk_parent = devm_clk_get_optional(dev, name);
		if (IS_ERR(channel->clk_parent))
			return PTR_ERR(channel->clk_parent);
	}

	return 0;
}