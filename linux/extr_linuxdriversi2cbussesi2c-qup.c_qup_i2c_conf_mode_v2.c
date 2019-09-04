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
struct qup_i2c_block {scalar_t__ is_rx_blk_mode; scalar_t__ is_tx_blk_mode; } ;
struct qup_i2c_dev {scalar_t__ base; struct qup_i2c_block blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUP_INPUT_BLK_MODE ; 
 scalar_t__ QUP_IO_MODE ; 
 scalar_t__ QUP_MX_INPUT_CNT ; 
 scalar_t__ QUP_MX_OUTPUT_CNT ; 
 scalar_t__ QUP_MX_READ_CNT ; 
 scalar_t__ QUP_MX_WRITE_CNT ; 
 int /*<<< orphan*/  QUP_OUTPUT_BLK_MODE ; 
 int /*<<< orphan*/  QUP_REPACK_EN ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qup_i2c_conf_mode_v2(struct qup_i2c_dev *qup)
{
	struct qup_i2c_block *blk = &qup->blk;
	u32 io_mode = QUP_REPACK_EN;

	if (blk->is_tx_blk_mode) {
		io_mode |= QUP_OUTPUT_BLK_MODE;
		writel(0, qup->base + QUP_MX_WRITE_CNT);
	} else {
		writel(0, qup->base + QUP_MX_OUTPUT_CNT);
	}

	if (blk->is_rx_blk_mode) {
		io_mode |= QUP_INPUT_BLK_MODE;
		writel(0, qup->base + QUP_MX_READ_CNT);
	} else {
		writel(0, qup->base + QUP_MX_INPUT_CNT);
	}

	writel(io_mode, qup->base + QUP_IO_MODE);
}