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
typedef  int /*<<< orphan*/  u8 ;
struct cxd2880_io {int (* write_regs ) (struct cxd2880_io*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
typedef  enum cxd2880_io_tgt { ____Placeholder_cxd2880_io_tgt } cxd2880_io_tgt ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct cxd2880_io*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int cxd2880_io_common_write_one_reg(struct cxd2880_io *io,
				    enum cxd2880_io_tgt tgt,
				    u8 sub_address, u8 data)
{
	if (!io)
		return -EINVAL;

	return io->write_regs(io, tgt, sub_address, &data, 1);
}