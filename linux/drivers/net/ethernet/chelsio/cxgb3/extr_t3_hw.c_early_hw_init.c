#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct adapter_info {int gpio_out; } ;
struct TYPE_3__ {int cclk; } ;
struct TYPE_4__ {scalar_t__ rev; TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_I2C_CFG ; 
 int /*<<< orphan*/  A_MC5_DB_SERVER_INDEX ; 
 int /*<<< orphan*/  A_SG_OCO_BASE ; 
 int /*<<< orphan*/  A_T3DBG_GPIO_EN ; 
 int /*<<< orphan*/  A_XGM_PORT_CFG ; 
 int F_CLKDIVRESET_ ; 
 int F_ENRGMII ; 
 int F_GPIO0_OEN ; 
 int F_GPIO0_OUT_VAL ; 
 int V_BASE1 (int) ; 
 int V_I2C_CLKDIV (int) ; 
 int V_PORTSPEED (int) ; 
 int /*<<< orphan*/  XGM_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_10G (struct adapter*) ; 
 int /*<<< orphan*/  mi1_init (struct adapter*,struct adapter_info const*) ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uses_xaui (struct adapter*) ; 

__attribute__((used)) static void early_hw_init(struct adapter *adapter,
			  const struct adapter_info *ai)
{
	u32 val = V_PORTSPEED(is_10G(adapter) ? 3 : 2);

	mi1_init(adapter, ai);
	t3_write_reg(adapter, A_I2C_CFG,	/* set for 80KHz */
		     V_I2C_CLKDIV(adapter->params.vpd.cclk / 80 - 1));
	t3_write_reg(adapter, A_T3DBG_GPIO_EN,
		     ai->gpio_out | F_GPIO0_OEN | F_GPIO0_OUT_VAL);
	t3_write_reg(adapter, A_MC5_DB_SERVER_INDEX, 0);
	t3_write_reg(adapter, A_SG_OCO_BASE, V_BASE1(0xfff));

	if (adapter->params.rev == 0 || !uses_xaui(adapter))
		val |= F_ENRGMII;

	/* Enable MAC clocks so we can access the registers */
	t3_write_reg(adapter, A_XGM_PORT_CFG, val);
	t3_read_reg(adapter, A_XGM_PORT_CFG);

	val |= F_CLKDIVRESET_;
	t3_write_reg(adapter, A_XGM_PORT_CFG, val);
	t3_read_reg(adapter, A_XGM_PORT_CFG);
	t3_write_reg(adapter, XGM_REG(A_XGM_PORT_CFG, 1), val);
	t3_read_reg(adapter, A_XGM_PORT_CFG);
}