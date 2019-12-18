#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_52__   TYPE_6__ ;
typedef  struct TYPE_51__   TYPE_5__ ;
typedef  struct TYPE_50__   TYPE_4__ ;
typedef  struct TYPE_49__   TYPE_3__ ;
typedef  struct TYPE_48__   TYPE_2__ ;
typedef  struct TYPE_47__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_51__ {scalar_t__ xtal_share_type; scalar_t__ stationary_use; scalar_t__ is_cxd2881gg; } ;
struct cxd2880_tnrdmd {scalar_t__ chip_id; TYPE_6__* io; TYPE_5__ create_param; TYPE_4__* lna_thrs_tbl_cable; TYPE_2__* lna_thrs_tbl_air; } ;
struct TYPE_52__ {int (* write_reg ) (TYPE_6__*,int /*<<< orphan*/ ,int,int) ;int (* write_regs ) (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ;int (* read_regs ) (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ;} ;
struct TYPE_50__ {TYPE_3__* thrs; } ;
struct TYPE_49__ {int off_on; int on_off; } ;
struct TYPE_48__ {TYPE_1__* thrs; } ;
struct TYPE_47__ {int off_on; int on_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 scalar_t__ CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X ; 
 scalar_t__ CXD2880_TNRDMD_XTAL_SHARE_SLAVE ; 
 int EINVAL ; 
 int cxd2880_io_write_multi_regs (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rf_init1_seq1 ; 
 int /*<<< orphan*/  rf_init1_seq2 ; 
 int /*<<< orphan*/  rf_init1_seq3 ; 
 int /*<<< orphan*/  rf_init1_seq4 ; 
 int /*<<< orphan*/  rf_init1_seq5 ; 
 int /*<<< orphan*/  rf_init1_seq6 ; 
 int /*<<< orphan*/  rf_init1_seq7 ; 
 int /*<<< orphan*/  rf_init1_seq8 ; 
 int /*<<< orphan*/  rf_init1_seq9 ; 
 int stub1 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub10 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub11 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub12 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub13 (TYPE_6__*,int /*<<< orphan*/ ,int,int const*,int) ; 
 int stub14 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub15 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub16 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub17 (TYPE_6__*,int /*<<< orphan*/ ,int,int const*,int) ; 
 int stub18 (TYPE_6__*,int /*<<< orphan*/ ,int,int const*,int) ; 
 int stub19 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub2 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub20 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub21 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub22 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub23 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub24 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub25 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub26 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub27 (TYPE_6__*,int /*<<< orphan*/ ,int,int const*,int) ; 
 int stub28 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub29 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub30 (TYPE_6__*,int /*<<< orphan*/ ,int,int const*,int) ; 
 int stub31 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub32 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub33 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub34 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub35 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub36 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub37 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub38 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub39 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub40 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub5 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub6 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub7 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub8 (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int stub9 (TYPE_6__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rf_init1(struct cxd2880_tnrdmd *tnr_dmd)
{
	u8 data[8] = { 0 };
	static const u8 rf_init1_cdata1[40] = {
		0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
		0x05, 0x05, 0x04, 0x04, 0x04, 0x03, 0x03,
		0x03, 0x04, 0x04, 0x05, 0x05, 0x05, 0x02,
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
		0x02, 0x03, 0x02, 0x01, 0x01, 0x01, 0x02,
		0x02, 0x03, 0x04, 0x04, 0x04
	};

	static const u8 rf_init1_cdata2[5] = {0xff, 0x00, 0x00, 0x00, 0x00};
	static const u8 rf_init1_cdata3[80] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
		0x01, 0x00, 0x02, 0x00, 0x63, 0x00, 0x00,
		0x00, 0x03, 0x00, 0x04, 0x00, 0x04, 0x00,
		0x06, 0x00, 0x06, 0x00, 0x08, 0x00, 0x09,
		0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0d, 0x00,
		0x0d, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f,
		0x00, 0x10, 0x00, 0x79, 0x00, 0x00, 0x00,
		0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01,
		0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
		0x04, 0x00, 0x04, 0x00, 0x06, 0x00, 0x05,
		0x00, 0x07, 0x00, 0x07, 0x00, 0x08, 0x00,
		0x0a, 0x03, 0xe0
	};

	static const u8 rf_init1_cdata4[8] = {
		0x20, 0x20, 0x30, 0x41, 0x50, 0x5f, 0x6f, 0x80
	};

	static const u8 rf_init1_cdata5[50] = {
		0x00, 0x09, 0x00, 0x08, 0x00, 0x07, 0x00,
		0x06, 0x00, 0x05, 0x00, 0x03, 0x00, 0x02,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00,
		0x06, 0x00, 0x08, 0x00, 0x08, 0x00, 0x0c,
		0x00, 0x0c, 0x00, 0x0d, 0x00, 0x0f, 0x00,
		0x0e, 0x00, 0x0e, 0x00, 0x10, 0x00, 0x0f,
		0x00, 0x0e, 0x00, 0x10, 0x00, 0x0f, 0x00,
		0x0e
	};

	u8 addr = 0;
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x00);
	if (ret)
		return ret;
	data[0] = 0x01;
	data[1] = 0x00;
	data[2] = 0x01;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x21, data, 3);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	if (ret)
		return ret;
	data[0] = 0x01;
	data[1] = 0x01;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x17, data, 2);
	if (ret)
		return ret;

	if (tnr_dmd->create_param.stationary_use) {
		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_SYS,
					     0x1a, 0x06);
		if (ret)
			return ret;
	}

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq1,
					  ARRAY_SIZE(rf_init1_seq1));
	if (ret)
		return ret;

	data[0] = 0x00;
	if (tnr_dmd->create_param.is_cxd2881gg &&
	    tnr_dmd->create_param.xtal_share_type ==
		CXD2880_TNRDMD_XTAL_SHARE_SLAVE)
		data[1] = 0x00;
	else
		data[1] = 0x1f;
	data[2] = 0x0a;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xb5, data, 3);
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq2,
					  ARRAY_SIZE(rf_init1_seq2));
	if (ret)
		return ret;

	if (tnr_dmd->chip_id == CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X) {
		data[0] = 0x34;
		data[1] = 0x2c;
	} else {
		data[0] = 0x2f;
		data[1] = 0x25;
	}
	data[2] = 0x15;
	data[3] = 0x19;
	data[4] = 0x1b;
	data[5] = 0x15;
	data[6] = 0x19;
	data[7] = 0x1b;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xd9, data, 8);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x11);
	if (ret)
		return ret;
	data[0] = 0x6c;
	data[1] = 0x10;
	data[2] = 0xa6;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x44, data, 3);
	if (ret)
		return ret;
	data[0] = 0x16;
	data[1] = 0xa8;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x50, data, 2);
	if (ret)
		return ret;
	data[0] = 0x00;
	data[1] = 0x22;
	data[2] = 0x00;
	data[3] = 0x88;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x62, data, 4);
	if (ret)
		return ret;
	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x74, 0x75);
	if (ret)
		return ret;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x7f, rf_init1_cdata1, 40);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x16);
	if (ret)
		return ret;
	data[0] = 0x00;
	data[1] = 0x71;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x10, data, 2);
	if (ret)
		return ret;
	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x23, 0x89);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x27, rf_init1_cdata2, 5);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x3a, rf_init1_cdata3, 80);
	if (ret)
		return ret;

	data[0] = 0x03;
	data[1] = 0xe0;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xbc, data, 2);
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq3,
					  ARRAY_SIZE(rf_init1_seq3));
	if (ret)
		return ret;

	if (tnr_dmd->create_param.stationary_use) {
		data[0] = 0x06;
		data[1] = 0x07;
		data[2] = 0x1a;
	} else {
		data[0] = 0x00;
		data[1] = 0x08;
		data[2] = 0x19;
	}
	data[3] = 0x0e;
	data[4] = 0x09;
	data[5] = 0x0e;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x12);
	if (ret)
		return ret;
	for (addr = 0x10; addr < 0x9f; addr += 6) {
		if (tnr_dmd->lna_thrs_tbl_air) {
			u8 idx = 0;

			idx = (addr - 0x10) / 6;
			data[0] =
			    tnr_dmd->lna_thrs_tbl_air->thrs[idx].off_on;
			data[1] =
			    tnr_dmd->lna_thrs_tbl_air->thrs[idx].on_off;
		}
		ret = tnr_dmd->io->write_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_SYS,
					      addr, data, 6);
		if (ret)
			return ret;
	}

	data[0] = 0x00;
	data[1] = 0x08;
	if (tnr_dmd->create_param.stationary_use)
		data[2] = 0x1a;
	else
		data[2] = 0x19;
	data[3] = 0x0e;
	data[4] = 0x09;
	data[5] = 0x0e;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x13);
	if (ret)
		return ret;
	for (addr = 0x10; addr < 0xcf; addr += 6) {
		if (tnr_dmd->lna_thrs_tbl_cable) {
			u8 idx = 0;

			idx = (addr - 0x10) / 6;
			data[0] =
			    tnr_dmd->lna_thrs_tbl_cable->thrs[idx].off_on;
			data[1] =
			    tnr_dmd->lna_thrs_tbl_cable->thrs[idx].on_off;
		}
		ret = tnr_dmd->io->write_regs(tnr_dmd->io,
					      CXD2880_IO_TGT_SYS,
					      addr, data, 6);
		if (ret)
			return ret;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x11);
	if (ret)
		return ret;
	data[0] = 0x08;
	data[1] = 0x09;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xbd, data, 2);
	if (ret)
		return ret;
	data[0] = 0x08;
	data[1] = 0x09;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xc4, data, 2);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0xc9, rf_init1_cdata4, 8);
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x14);
	if (ret)
		return ret;
	data[0] = 0x15;
	data[1] = 0x18;
	data[2] = 0x00;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x10, data, 3);
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq4,
					  ARRAY_SIZE(rf_init1_seq4));
	if (ret)
		return ret;

	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x12, rf_init1_cdata5, 50);
	if (ret)
		return ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	if (ret)
		return ret;
	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x10, data, 1);
	if (ret)
		return ret;
	if ((data[0] & 0x01) == 0x00)
		return -EINVAL;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq5,
					  ARRAY_SIZE(rf_init1_seq5));
	if (ret)
		return ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x0a);
	if (ret)
		return ret;
	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x11, data, 1);
	if (ret)
		return ret;
	if ((data[0] & 0x01) == 0x00)
		return -EINVAL;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  rf_init1_seq6,
					  ARRAY_SIZE(rf_init1_seq6));
	if (ret)
		return ret;

	data[0] = 0x00;
	data[1] = 0xfe;
	data[2] = 0xee;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x6e, data, 3);
	if (ret)
		return ret;
	data[0] = 0xa1;
	data[1] = 0x8b;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x8d, data, 2);
	if (ret)
		return ret;
	data[0] = 0x08;
	data[1] = 0x09;
	ret = tnr_dmd->io->write_regs(tnr_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x77, data, 2);
	if (ret)
		return ret;

	if (tnr_dmd->create_param.stationary_use) {
		ret = tnr_dmd->io->write_reg(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x80, 0xaa);
		if (ret)
			return ret;
	}

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  rf_init1_seq7,
					  ARRAY_SIZE(rf_init1_seq7));
	if (ret)
		return ret;

	ret = cxd2880_io_write_multi_regs(tnr_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  rf_init1_seq8,
					  ARRAY_SIZE(rf_init1_seq8));
	if (ret)
		return ret;

	usleep_range(1000, 2000);

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x1a);
	if (ret)
		return ret;
	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x10, data, 1);
	if (ret)
		return ret;
	if ((data[0] & 0x01) == 0x00)
		return -EINVAL;

	return cxd2880_io_write_multi_regs(tnr_dmd->io,
					   CXD2880_IO_TGT_SYS,
					   rf_init1_seq9,
					   ARRAY_SIZE(rf_init1_seq9));
}