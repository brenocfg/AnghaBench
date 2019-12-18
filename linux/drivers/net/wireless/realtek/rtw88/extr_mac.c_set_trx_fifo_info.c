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
typedef  void* u16 ;
struct rtw_fifo_conf {int rsvd_drv_pg_num; int txff_pg_num; int rsvd_pg_num; int acq_pg_num; int rsvd_boundary; int rsvd_drv_addr; void* rsvd_h2c_info_addr; void* rsvd_h2c_sta_info_addr; void* rsvd_h2cq_addr; void* rsvd_cpu_instr_addr; void* rsvd_fw_txbuf_addr; void* rsvd_csibuf_addr; } ;
struct rtw_dev {struct rtw_chip_info* chip; struct rtw_fifo_conf fifo; } ;
struct rtw_chip_info {int csi_buf_pg_num; int txff_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int RSVD_PG_CPU_INSTRUCTION_NUM ; 
 int RSVD_PG_FW_TXBUF_NUM ; 
 int RSVD_PG_H2CQ_NUM ; 
 int RSVD_PG_H2C_EXTRAINFO_NUM ; 
 int RSVD_PG_H2C_STATICINFO_NUM ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 

__attribute__((used)) static int set_trx_fifo_info(struct rtw_dev *rtwdev)
{
	struct rtw_fifo_conf *fifo = &rtwdev->fifo;
	struct rtw_chip_info *chip = rtwdev->chip;
	u16 cur_pg_addr;
	u8 csi_buf_pg_num = chip->csi_buf_pg_num;

	/* config rsvd page num */
	fifo->rsvd_drv_pg_num = 8;
	fifo->txff_pg_num = chip->txff_size >> 7;
	fifo->rsvd_pg_num = fifo->rsvd_drv_pg_num +
			   RSVD_PG_H2C_EXTRAINFO_NUM +
			   RSVD_PG_H2C_STATICINFO_NUM +
			   RSVD_PG_H2CQ_NUM +
			   RSVD_PG_CPU_INSTRUCTION_NUM +
			   RSVD_PG_FW_TXBUF_NUM +
			   csi_buf_pg_num;

	if (fifo->rsvd_pg_num > fifo->txff_pg_num)
		return -ENOMEM;

	fifo->acq_pg_num = fifo->txff_pg_num - fifo->rsvd_pg_num;
	fifo->rsvd_boundary = fifo->txff_pg_num - fifo->rsvd_pg_num;

	cur_pg_addr = fifo->txff_pg_num;
	cur_pg_addr -= csi_buf_pg_num;
	fifo->rsvd_csibuf_addr = cur_pg_addr;
	cur_pg_addr -= RSVD_PG_FW_TXBUF_NUM;
	fifo->rsvd_fw_txbuf_addr = cur_pg_addr;
	cur_pg_addr -= RSVD_PG_CPU_INSTRUCTION_NUM;
	fifo->rsvd_cpu_instr_addr = cur_pg_addr;
	cur_pg_addr -= RSVD_PG_H2CQ_NUM;
	fifo->rsvd_h2cq_addr = cur_pg_addr;
	cur_pg_addr -= RSVD_PG_H2C_STATICINFO_NUM;
	fifo->rsvd_h2c_sta_info_addr = cur_pg_addr;
	cur_pg_addr -= RSVD_PG_H2C_EXTRAINFO_NUM;
	fifo->rsvd_h2c_info_addr = cur_pg_addr;
	cur_pg_addr -= fifo->rsvd_drv_pg_num;
	fifo->rsvd_drv_addr = cur_pg_addr;

	if (fifo->rsvd_boundary != fifo->rsvd_drv_addr) {
		rtw_err(rtwdev, "wrong rsvd driver address\n");
		return -EINVAL;
	}

	return 0;
}