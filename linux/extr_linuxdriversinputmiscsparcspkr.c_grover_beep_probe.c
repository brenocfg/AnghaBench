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
struct grover_beep_info {void* freq_regs; void* enable_reg; } ;
struct TYPE_2__ {struct grover_beep_info grover; } ;
struct sparcspkr_state {char* name; TYPE_1__ u; int /*<<< orphan*/  lock; int /*<<< orphan*/  event; } ;
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  grover_spkr_event ; 
 int /*<<< orphan*/  kfree (struct sparcspkr_state*) ; 
 struct sparcspkr_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* of_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sparcspkr_state*) ; 
 int sparcspkr_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int grover_beep_probe(struct platform_device *op)
{
	struct sparcspkr_state *state;
	struct grover_beep_info *info;
	int err = -ENOMEM;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		goto out_err;

	state->name = "Sparc Grover Speaker";
	state->event = grover_spkr_event;
	spin_lock_init(&state->lock);

	info = &state->u.grover;
	info->freq_regs = of_ioremap(&op->resource[2], 0, 2, "grover beep freq");
	if (!info->freq_regs)
		goto out_free;

	info->enable_reg = of_ioremap(&op->resource[3], 0, 1, "grover beep enable");
	if (!info->enable_reg)
		goto out_unmap_freq_regs;

	platform_set_drvdata(op, state);

	err = sparcspkr_probe(&op->dev);
	if (err)
		goto out_clear_drvdata;

	return 0;

out_clear_drvdata:
	of_iounmap(&op->resource[3], info->enable_reg, 1);

out_unmap_freq_regs:
	of_iounmap(&op->resource[2], info->freq_regs, 2);
out_free:
	kfree(state);
out_err:
	return err;
}