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
typedef  int u8 ;
struct cxd2880_reg_value {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;
struct cxd2880_io {int (* write_reg ) (struct cxd2880_io*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  enum cxd2880_io_tgt { ____Placeholder_cxd2880_io_tgt } cxd2880_io_tgt ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct cxd2880_io*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cxd2880_io_write_multi_regs(struct cxd2880_io *io,
			     enum cxd2880_io_tgt tgt,
			     const struct cxd2880_reg_value reg_value[],
			     u8 size)
{
	int ret;
	int i;

	if (!io)
		return -EINVAL;

	for (i = 0; i < size ; i++) {
		ret = io->write_reg(io, tgt, reg_value[i].addr,
				    reg_value[i].value);
		if (ret)
			return ret;
	}

	return 0;
}