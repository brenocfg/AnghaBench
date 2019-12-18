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
struct TYPE_2__ {struct module* owner; int /*<<< orphan*/  get_rate; } ;
struct v4l2_clk_fixed {unsigned long rate; TYPE_1__ ops; } ;
struct v4l2_clk {int dummy; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct v4l2_clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct v4l2_clk*) ; 
 int /*<<< orphan*/  fixed_get_rate ; 
 int /*<<< orphan*/  kfree (struct v4l2_clk_fixed*) ; 
 struct v4l2_clk_fixed* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct v4l2_clk* v4l2_clk_register (TYPE_1__*,char const*,struct v4l2_clk_fixed*) ; 

struct v4l2_clk *__v4l2_clk_register_fixed(const char *dev_id,
				unsigned long rate, struct module *owner)
{
	struct v4l2_clk *clk;
	struct v4l2_clk_fixed *priv = kzalloc(sizeof(*priv), GFP_KERNEL);

	if (!priv)
		return ERR_PTR(-ENOMEM);

	priv->rate = rate;
	priv->ops.get_rate = fixed_get_rate;
	priv->ops.owner = owner;

	clk = v4l2_clk_register(&priv->ops, dev_id, priv);
	if (IS_ERR(clk))
		kfree(priv);

	return clk;
}