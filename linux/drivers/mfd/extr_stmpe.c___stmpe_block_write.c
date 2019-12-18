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
struct TYPE_2__ {int (* write_block ) (struct stmpe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmpe_dump_bytes (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int stub1 (struct stmpe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int __stmpe_block_write(struct stmpe *stmpe, u8 reg, u8 length,
			const u8 *values)
{
	int ret;

	dev_vdbg(stmpe->dev, "wr: regs %#x (%d)\n", reg, length);
	stmpe_dump_bytes("stmpe wr: ", values, length);

	ret = stmpe->ci->write_block(stmpe, reg, length, values);
	if (ret < 0)
		dev_err(stmpe->dev, "failed to write regs %#x: %d\n", reg, ret);

	return ret;
}