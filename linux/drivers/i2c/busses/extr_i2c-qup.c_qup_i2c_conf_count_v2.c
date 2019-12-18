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
typedef  int u32 ;
struct qup_i2c_block {int total_tx_len; int total_rx_len; scalar_t__ is_rx_blk_mode; scalar_t__ is_tx_blk_mode; } ;
struct qup_i2c_dev {int config_run; scalar_t__ base; struct qup_i2c_block blk; } ;

/* Variables and functions */
 int I2C_MINI_CORE ; 
 int I2C_N_VAL_V2 ; 
 scalar_t__ QUP_CONFIG ; 
 scalar_t__ QUP_MX_INPUT_CNT ; 
 scalar_t__ QUP_MX_OUTPUT_CNT ; 
 scalar_t__ QUP_MX_READ_CNT ; 
 scalar_t__ QUP_MX_WRITE_CNT ; 
 int QUP_NO_INPUT ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void qup_i2c_conf_count_v2(struct qup_i2c_dev *qup)
{
	struct qup_i2c_block *blk = &qup->blk;
	u32 qup_config = I2C_MINI_CORE | I2C_N_VAL_V2;

	if (blk->is_tx_blk_mode)
		writel(qup->config_run | blk->total_tx_len,
		       qup->base + QUP_MX_OUTPUT_CNT);
	else
		writel(qup->config_run | blk->total_tx_len,
		       qup->base + QUP_MX_WRITE_CNT);

	if (blk->total_rx_len) {
		if (blk->is_rx_blk_mode)
			writel(qup->config_run | blk->total_rx_len,
			       qup->base + QUP_MX_INPUT_CNT);
		else
			writel(qup->config_run | blk->total_rx_len,
			       qup->base + QUP_MX_READ_CNT);
	} else {
		qup_config |= QUP_NO_INPUT;
	}

	writel(qup_config, qup->base + QUP_CONFIG);
}