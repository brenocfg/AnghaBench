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
struct TYPE_2__ {char const* con_id; struct clk* clk; int /*<<< orphan*/  dev_id; } ;
struct clk {unsigned int bits; TYPE_1__ cl; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clkdev_add (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  gptu_disable ; 
 int /*<<< orphan*/  gptu_enable ; 
 struct clk* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clkdev_add_gptu(struct device *dev, const char *con,
							unsigned int timer)
{
	struct clk *clk = kzalloc(sizeof(struct clk), GFP_KERNEL);

	clk->cl.dev_id = dev_name(dev);
	clk->cl.con_id = con;
	clk->cl.clk = clk;
	clk->enable = gptu_enable;
	clk->disable = gptu_disable;
	clk->bits = timer;
	clkdev_add(&clk->cl);
}