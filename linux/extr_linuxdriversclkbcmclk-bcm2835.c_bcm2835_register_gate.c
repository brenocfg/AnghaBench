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
struct clk {int dummy; } ;
struct bcm2835_gate_data {scalar_t__ ctl_reg; int /*<<< orphan*/  parent; int /*<<< orphan*/  name; } ;
struct bcm2835_cprman {int /*<<< orphan*/  regs_lock; scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CLK_IGNORE_UNUSED ; 
 int CLK_SET_RATE_GATE ; 
 int /*<<< orphan*/  CM_GATE_BIT ; 
 struct clk* clk_register_gate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct clk *bcm2835_register_gate(struct bcm2835_cprman *cprman,
					 const struct bcm2835_gate_data *data)
{
	return clk_register_gate(cprman->dev, data->name, data->parent,
				 CLK_IGNORE_UNUSED | CLK_SET_RATE_GATE,
				 cprman->regs + data->ctl_reg,
				 CM_GATE_BIT, 0, &cprman->regs_lock);
}