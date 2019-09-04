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
struct bbc_beep_info {int /*<<< orphan*/  regs; int /*<<< orphan*/  clock_freq; } ;
struct TYPE_2__ {struct bbc_beep_info bbc; } ;
struct sparcspkr_state {char* name; TYPE_1__ u; int /*<<< orphan*/  lock; int /*<<< orphan*/  event; } ;
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bbc_spkr_event ; 
 int /*<<< orphan*/  kfree (struct sparcspkr_state*) ; 
 struct sparcspkr_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int /*<<< orphan*/  of_getintprop_default (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sparcspkr_state*) ; 
 int sparcspkr_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bbc_beep_probe(struct platform_device *op)
{
	struct sparcspkr_state *state;
	struct bbc_beep_info *info;
	struct device_node *dp;
	int err = -ENOMEM;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		goto out_err;

	state->name = "Sparc BBC Speaker";
	state->event = bbc_spkr_event;
	spin_lock_init(&state->lock);

	dp = of_find_node_by_path("/");
	err = -ENODEV;
	if (!dp)
		goto out_free;

	info = &state->u.bbc;
	info->clock_freq = of_getintprop_default(dp, "clock-frequency", 0);
	if (!info->clock_freq)
		goto out_free;

	info->regs = of_ioremap(&op->resource[0], 0, 6, "bbc beep");
	if (!info->regs)
		goto out_free;

	platform_set_drvdata(op, state);

	err = sparcspkr_probe(&op->dev);
	if (err)
		goto out_clear_drvdata;

	return 0;

out_clear_drvdata:
	of_iounmap(&op->resource[0], info->regs, 6);

out_free:
	kfree(state);
out_err:
	return err;
}