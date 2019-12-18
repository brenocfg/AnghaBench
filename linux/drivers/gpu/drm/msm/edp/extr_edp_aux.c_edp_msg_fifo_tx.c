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
typedef  int u32 ;
struct edp_aux {scalar_t__ base; } ;
struct drm_dp_aux_msg {int request; int* buffer; int size; int address; } ;

/* Variables and functions */
 int AUX_CMD_FIFO_LEN ; 
 int BIT (int) ; 
 int DP_AUX_I2C_READ ; 
 int DP_AUX_NATIVE_READ ; 
 int DP_AUX_NATIVE_WRITE ; 
 int EDP_AUX_DATA_DATA (int) ; 
 int EDP_AUX_DATA_INDEX_WRITE ; 
 int EDP_AUX_TRANS_CTRL_GO ; 
 int EDP_AUX_TRANS_CTRL_I2C ; 
 int EINVAL ; 
 scalar_t__ REG_EDP_AUX_DATA ; 
 scalar_t__ REG_EDP_AUX_TRANS_CTRL ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int) ; 

__attribute__((used)) static int edp_msg_fifo_tx(struct edp_aux *aux, struct drm_dp_aux_msg *msg)
{
	u32 data[4];
	u32 reg, len;
	bool native = msg->request & (DP_AUX_NATIVE_WRITE & DP_AUX_NATIVE_READ);
	bool read = msg->request & (DP_AUX_I2C_READ & DP_AUX_NATIVE_READ);
	u8 *msgdata = msg->buffer;
	int i;

	if (read)
		len = 4;
	else
		len = msg->size + 4;

	/*
	 * cmd fifo only has depth of 144 bytes
	 */
	if (len > AUX_CMD_FIFO_LEN)
		return -EINVAL;

	/* Pack cmd and write to HW */
	data[0] = (msg->address >> 16) & 0xf;	/* addr[19:16] */
	if (read)
		data[0] |=  BIT(4);		/* R/W */

	data[1] = (msg->address >> 8) & 0xff;	/* addr[15:8] */
	data[2] = msg->address & 0xff;		/* addr[7:0] */
	data[3] = (msg->size - 1) & 0xff;	/* len[7:0] */

	for (i = 0; i < len; i++) {
		reg = (i < 4) ? data[i] : msgdata[i - 4];
		reg = EDP_AUX_DATA_DATA(reg); /* index = 0, write */
		if (i == 0)
			reg |= EDP_AUX_DATA_INDEX_WRITE;
		edp_write(aux->base + REG_EDP_AUX_DATA, reg);
	}

	reg = 0; /* Transaction number is always 1 */
	if (!native) /* i2c */
		reg |= EDP_AUX_TRANS_CTRL_I2C;

	reg |= EDP_AUX_TRANS_CTRL_GO;
	edp_write(aux->base + REG_EDP_AUX_TRANS_CTRL, reg);

	return 0;
}