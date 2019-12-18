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
typedef  int /*<<< orphan*/  u8 ;
struct stmpe {int /*<<< orphan*/  dev; TYPE_1__* ci; } ;
struct TYPE_2__ {int (* read_byte ) (struct stmpe*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct stmpe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __stmpe_reg_read(struct stmpe *stmpe, u8 reg)
{
	int ret;

	ret = stmpe->ci->read_byte(stmpe, reg);
	if (ret < 0)
		dev_err(stmpe->dev, "failed to read reg %#x: %d\n", reg, ret);

	dev_vdbg(stmpe->dev, "rd: reg %#x => data %#x\n", reg, ret);

	return ret;
}