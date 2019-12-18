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
struct i2c_msg {size_t len; } ;
struct geni_se {scalar_t__ base; } ;
struct geni_i2c_dev {int err; scalar_t__ cur_wr; int /*<<< orphan*/  done; struct geni_se se; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GENI_SE_DMA ; 
 int /*<<< orphan*/  GENI_SE_FIFO ; 
 int /*<<< orphan*/  I2C_WRITE ; 
 scalar_t__ SE_GENI_TX_WATERMARK_REG ; 
 scalar_t__ SE_I2C_TX_TRANS_LEN ; 
 int /*<<< orphan*/  XFER_TIMEOUT ; 
 int /*<<< orphan*/  geni_i2c_abort_xfer (struct geni_i2c_dev*) ; 
 int /*<<< orphan*/  geni_i2c_tx_fsm_rst (struct geni_i2c_dev*) ; 
 int /*<<< orphan*/  geni_se_select_mode (struct geni_se*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geni_se_setup_m_cmd (struct geni_se*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ geni_se_tx_dma_prep (struct geni_se*,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geni_se_tx_dma_unprep (struct geni_se*,int /*<<< orphan*/ ,size_t) ; 
 void* i2c_get_dma_safe_msg_buf (struct i2c_msg*,int) ; 
 int /*<<< orphan*/  i2c_put_dma_safe_msg_buf (void*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  of_machine_is_compatible (char*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int geni_i2c_tx_one_msg(struct geni_i2c_dev *gi2c, struct i2c_msg *msg,
				u32 m_param)
{
	dma_addr_t tx_dma;
	unsigned long time_left;
	void *dma_buf = NULL;
	struct geni_se *se = &gi2c->se;
	size_t len = msg->len;

	if (!of_machine_is_compatible("lenovo,yoga-c630"))
		dma_buf = i2c_get_dma_safe_msg_buf(msg, 32);

	if (dma_buf)
		geni_se_select_mode(se, GENI_SE_DMA);
	else
		geni_se_select_mode(se, GENI_SE_FIFO);

	writel_relaxed(len, se->base + SE_I2C_TX_TRANS_LEN);
	geni_se_setup_m_cmd(se, I2C_WRITE, m_param);

	if (dma_buf && geni_se_tx_dma_prep(se, dma_buf, len, &tx_dma)) {
		geni_se_select_mode(se, GENI_SE_FIFO);
		i2c_put_dma_safe_msg_buf(dma_buf, msg, false);
		dma_buf = NULL;
	}

	if (!dma_buf) /* Get FIFO IRQ */
		writel_relaxed(1, se->base + SE_GENI_TX_WATERMARK_REG);

	time_left = wait_for_completion_timeout(&gi2c->done, XFER_TIMEOUT);
	if (!time_left)
		geni_i2c_abort_xfer(gi2c);

	gi2c->cur_wr = 0;
	if (dma_buf) {
		if (gi2c->err)
			geni_i2c_tx_fsm_rst(gi2c);
		geni_se_tx_dma_unprep(se, tx_dma, len);
		i2c_put_dma_safe_msg_buf(dma_buf, msg, !gi2c->err);
	}

	return gi2c->err;
}