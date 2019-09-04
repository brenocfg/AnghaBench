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
struct cxd2880_io {int (* read_regs ) (struct cxd2880_io*,int,int,int*,int) ;int (* write_reg ) (struct cxd2880_io*,int,int,int) ;} ;
typedef  enum cxd2880_io_tgt { ____Placeholder_cxd2880_io_tgt } cxd2880_io_tgt ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct cxd2880_io*,int,int,int*,int) ; 
 int stub2 (struct cxd2880_io*,int,int,int) ; 

int cxd2880_io_set_reg_bits(struct cxd2880_io *io,
			    enum cxd2880_io_tgt tgt,
			    u8 sub_address, u8 data, u8 mask)
{
	int ret;

	if (!io)
		return -EINVAL;

	if (mask == 0x00)
		return 0;

	if (mask != 0xff) {
		u8 rdata = 0x00;

		ret = io->read_regs(io, tgt, sub_address, &rdata, 1);
		if (ret)
			return ret;

		data = (data & mask) | (rdata & (mask ^ 0xff));
	}

	return io->write_reg(io, tgt, sub_address, data);
}