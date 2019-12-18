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
typedef  int u16 ;
struct mtk_i2c {scalar_t__ base; } ;
struct i2c_msg {int flags; int addr; int len; int* buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int I2C_M_IGNORE_NAK ; 
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 scalar_t__ REG_SM0D0_REG ; 
 scalar_t__ REG_SM0D1_REG ; 
 int SM0CTL1_READ ; 
 int SM0CTL1_READ_LAST ; 
 int SM0CTL1_WRITE ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 struct mtk_i2c* i2c_get_adapdata (struct i2c_adapter*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int mtk_i2c_check_ack (struct mtk_i2c*,int) ; 
 int /*<<< orphan*/  mtk_i2c_dump_reg (struct mtk_i2c*) ; 
 int mtk_i2c_master_cmd (struct mtk_i2c*,int,int) ; 
 int mtk_i2c_master_start (struct mtk_i2c*) ; 
 int mtk_i2c_master_stop (struct mtk_i2c*) ; 
 int /*<<< orphan*/  mtk_i2c_reset (struct mtk_i2c*) ; 
 int mtk_i2c_wait_idle (struct mtk_i2c*) ; 

__attribute__((used)) static int mtk_i2c_master_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			       int num)
{
	struct mtk_i2c *i2c;
	struct i2c_msg *pmsg;
	u16 addr;
	int i, j, ret, len, page_len;
	u32 cmd;
	u32 data[2];

	i2c = i2c_get_adapdata(adap);

	for (i = 0; i < num; i++) {
		pmsg = &msgs[i];

		/* wait hardware idle */
		ret = mtk_i2c_wait_idle(i2c);
		if (ret)
			goto err_timeout;

		/* start sequence */
		ret = mtk_i2c_master_start(i2c);
		if (ret)
			goto err_timeout;

		/* write address */
		if (pmsg->flags & I2C_M_TEN) {
			/* 10 bits address */
			addr = 0xf0 | ((pmsg->addr >> 7) & 0x06);
			addr |= (pmsg->addr & 0xff) << 8;
			if (pmsg->flags & I2C_M_RD)
				addr |= 1;
			iowrite32(addr, i2c->base + REG_SM0D0_REG);
			ret = mtk_i2c_master_cmd(i2c, SM0CTL1_WRITE, 2);
			if (ret)
				goto err_timeout;
		} else {
			/* 7 bits address */
			addr = i2c_8bit_addr_from_msg(pmsg);
			iowrite32(addr, i2c->base + REG_SM0D0_REG);
			ret = mtk_i2c_master_cmd(i2c, SM0CTL1_WRITE, 1);
			if (ret)
				goto err_timeout;
		}

		/* check address ACK */
		if (!(pmsg->flags & I2C_M_IGNORE_NAK)) {
			ret = mtk_i2c_check_ack(i2c, BIT(0));
			if (ret)
				goto err_ack;
		}

		/* transfer data */
		for (len = pmsg->len, j = 0; len > 0; len -= 8, j += 8) {
			page_len = (len >= 8) ? 8 : len;

			if (pmsg->flags & I2C_M_RD) {
				cmd = (len > 8) ?
					SM0CTL1_READ : SM0CTL1_READ_LAST;
			} else {
				memcpy(data, &pmsg->buf[j], page_len);
				iowrite32(data[0], i2c->base + REG_SM0D0_REG);
				iowrite32(data[1], i2c->base + REG_SM0D1_REG);
				cmd = SM0CTL1_WRITE;
			}

			ret = mtk_i2c_master_cmd(i2c, cmd, page_len);
			if (ret)
				goto err_timeout;

			if (pmsg->flags & I2C_M_RD) {
				data[0] = ioread32(i2c->base + REG_SM0D0_REG);
				data[1] = ioread32(i2c->base + REG_SM0D1_REG);
				memcpy(&pmsg->buf[j], data, page_len);
			} else {
				if (!(pmsg->flags & I2C_M_IGNORE_NAK)) {
					ret = mtk_i2c_check_ack(i2c,
								(1 << page_len)
								- 1);
					if (ret)
						goto err_ack;
				}
			}
		}
	}

	ret = mtk_i2c_master_stop(i2c);
	if (ret)
		goto err_timeout;

	/* the return value is number of executed messages */
	return i;

err_ack:
	ret = mtk_i2c_master_stop(i2c);
	if (ret)
		goto err_timeout;
	return -ENXIO;

err_timeout:
	mtk_i2c_dump_reg(i2c);
	mtk_i2c_reset(i2c);
	return ret;
}