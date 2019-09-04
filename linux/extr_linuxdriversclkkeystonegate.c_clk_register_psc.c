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
struct device {int dummy; } ;
struct clk_psc_data {int dummy; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct clk_psc {TYPE_1__ hw; int /*<<< orphan*/ * lock; struct clk_psc_data* psc_data; } ;
struct clk_init_data {char const* name; char const** parent_names; int num_parents; scalar_t__ flags; int /*<<< orphan*/ * ops; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_psc_ops ; 
 struct clk* clk_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct clk_psc*) ; 
 struct clk_psc* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk *clk_register_psc(struct device *dev,
			const char *name,
			const char *parent_name,
			struct clk_psc_data *psc_data,
			spinlock_t *lock)
{
	struct clk_init_data init;
	struct clk_psc *psc;
	struct clk *clk;

	psc = kzalloc(sizeof(*psc), GFP_KERNEL);
	if (!psc)
		return ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_psc_ops;
	init.flags = 0;
	init.parent_names = (parent_name ? &parent_name : NULL);
	init.num_parents = (parent_name ? 1 : 0);

	psc->psc_data = psc_data;
	psc->lock = lock;
	psc->hw.init = &init;

	clk = clk_register(NULL, &psc->hw);
	if (IS_ERR(clk))
		kfree(psc);

	return clk;
}