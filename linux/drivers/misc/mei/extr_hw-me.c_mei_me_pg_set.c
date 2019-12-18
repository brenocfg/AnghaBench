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
typedef  int /*<<< orphan*/  u32 ;
struct mei_me_hw {int dummy; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_HPG_CSR ; 
 int /*<<< orphan*/  H_HPG_CSR_PGI ; 
 int /*<<< orphan*/  mei_me_reg_read (struct mei_me_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_reg_write (struct mei_me_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 
 int /*<<< orphan*/  trace_mei_reg_read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mei_reg_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mei_me_pg_set(struct mei_device *dev)
{
	struct mei_me_hw *hw = to_me_hw(dev);
	u32 reg;

	reg = mei_me_reg_read(hw, H_HPG_CSR);
	trace_mei_reg_read(dev->dev, "H_HPG_CSR", H_HPG_CSR, reg);

	reg |= H_HPG_CSR_PGI;

	trace_mei_reg_write(dev->dev, "H_HPG_CSR", H_HPG_CSR, reg);
	mei_me_reg_write(hw, H_HPG_CSR, reg);
}