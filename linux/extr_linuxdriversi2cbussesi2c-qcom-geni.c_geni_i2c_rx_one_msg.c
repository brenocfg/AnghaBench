#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i2c_msg {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {scalar_t__ base; } ;
struct geni_i2c_dev {int err; TYPE_1__ se; scalar_t__ cur_rd; int /*<<< orphan*/  done; struct i2c_msg* cur; } ;
typedef  enum geni_se_xfer_mode { ____Placeholder_geni_se_xfer_mode } geni_se_xfer_mode ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int GENI_SE_DMA ; 
 int GENI_SE_FIFO ; 
 int /*<<< orphan*/  I2C_READ ; 
 scalar_t__ SE_I2C_RX_TRANS_LEN ; 
 unsigned long XFER_TIMEOUT ; 
 int /*<<< orphan*/  geni_i2c_abort_xfer (struct geni_i2c_dev*) ; 
 int /*<<< orphan*/  geni_i2c_rx_fsm_rst (struct geni_i2c_dev*) ; 
 int geni_se_rx_dma_prep (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geni_se_rx_dma_unprep (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geni_se_select_mode (TYPE_1__*,int) ; 
 int /*<<< orphan*/  geni_se_setup_m_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* i2c_get_dma_safe_msg_buf (struct i2c_msg*,int) ; 
 int /*<<< orphan*/  i2c_put_dma_safe_msg_buf (void*,struct i2c_msg*,int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int geni_i2c_rx_one_msg(struct geni_i2c_dev *gi2c, struct i2c_msg *msg,
				u32 m_param)
{
	dma_addr_t rx_dma;
	enum geni_se_xfer_mode mode;
	unsigned long time_left = XFER_TIMEOUT;
	void *dma_buf;

	gi2c->cur = msg;
	mode = GENI_SE_FIFO;
	dma_buf = i2c_get_dma_safe_msg_buf(msg, 32);
	if (dma_buf)
		mode = GENI_SE_DMA;

	geni_se_select_mode(&gi2c->se, mode);
	writel_relaxed(msg->len, gi2c->se.base + SE_I2C_RX_TRANS_LEN);
	geni_se_setup_m_cmd(&gi2c->se, I2C_READ, m_param);
	if (mode == GENI_SE_DMA) {
		int ret;

		ret = geni_se_rx_dma_prep(&gi2c->se, dma_buf, msg->len,
								&rx_dma);
		if (ret) {
			mode = GENI_SE_FIFO;
			geni_se_select_mode(&gi2c->se, mode);
			i2c_put_dma_safe_msg_buf(dma_buf, msg, false);
		}
	}

	time_left = wait_for_completion_timeout(&gi2c->done, XFER_TIMEOUT);
	if (!time_left)
		geni_i2c_abort_xfer(gi2c);

	gi2c->cur_rd = 0;
	if (mode == GENI_SE_DMA) {
		if (gi2c->err)
			geni_i2c_rx_fsm_rst(gi2c);
		geni_se_rx_dma_unprep(&gi2c->se, rx_dma, msg->len);
		i2c_put_dma_safe_msg_buf(dma_buf, msg, !gi2c->err);
	}
	return gi2c->err;
}