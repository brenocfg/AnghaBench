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
struct i2c_client {int flags; int addr; int /*<<< orphan*/  adapter; } ;
struct axxia_i2c_dev {scalar_t__ base; struct i2c_client* slave; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ GLOBAL_CONTROL ; 
 int GLOBAL_MST_EN ; 
 int GLOBAL_SLV_EN ; 
 int I2C_CLIENT_TEN ; 
 scalar_t__ INTERRUPT_ENABLE ; 
 int INT_MST ; 
 int INT_SLV ; 
 scalar_t__ SLV_ADDR_1 ; 
 scalar_t__ SLV_ADDR_DEC_CTL ; 
 int SLV_ADDR_DEC_SA1E ; 
 int SLV_ADDR_DEC_SA1M ; 
 scalar_t__ SLV_INT_ENABLE ; 
 int SLV_RX_ACSA1 ; 
 scalar_t__ SLV_RX_CTL ; 
 int SLV_STATUS_RFH ; 
 int SLV_STATUS_SRC1 ; 
 int SLV_STATUS_SRND1 ; 
 int SLV_STATUS_SRRS1 ; 
 int SLV_STATUS_SRS1 ; 
 struct axxia_i2c_dev* i2c_get_adapdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int axxia_i2c_reg_slave(struct i2c_client *slave)
{
	struct axxia_i2c_dev *idev = i2c_get_adapdata(slave->adapter);
	u32 slv_int_mask = SLV_STATUS_RFH;
	u32 dec_ctl;

	if (idev->slave)
		return -EBUSY;

	idev->slave = slave;

	/* Enable slave mode as well */
	writel(GLOBAL_MST_EN | GLOBAL_SLV_EN, idev->base + GLOBAL_CONTROL);
	writel(INT_MST | INT_SLV, idev->base + INTERRUPT_ENABLE);

	/* Set slave address */
	dec_ctl = SLV_ADDR_DEC_SA1E;
	if (slave->flags & I2C_CLIENT_TEN)
		dec_ctl |= SLV_ADDR_DEC_SA1M;

	writel(SLV_RX_ACSA1, idev->base + SLV_RX_CTL);
	writel(dec_ctl, idev->base + SLV_ADDR_DEC_CTL);
	writel(slave->addr, idev->base + SLV_ADDR_1);

	/* Enable interrupts */
	slv_int_mask |= SLV_STATUS_SRS1 | SLV_STATUS_SRRS1 | SLV_STATUS_SRND1;
	slv_int_mask |= SLV_STATUS_SRC1;
	writel(slv_int_mask, idev->base + SLV_INT_ENABLE);

	return 0;
}