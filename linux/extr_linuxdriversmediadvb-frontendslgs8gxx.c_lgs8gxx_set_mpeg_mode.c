#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct lgs8gxx_state {TYPE_1__* config; } ;
struct TYPE_2__ {scalar_t__ prod; } ;

/* Variables and functions */
 scalar_t__ LGS8GXX_PROD_LGS8G75 ; 
 int TS_CLK_FREERUN ; 
 int TS_CLK_GATED ; 
 int TS_CLK_INVERTED ; 
 int TS_CLK_NORMAL ; 
 int TS_PARALLEL ; 
 int TS_SERIAL ; 
 int lgs8gxx_read_reg (struct lgs8gxx_state*,int,int*) ; 
 int lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 

__attribute__((used)) static int lgs8gxx_set_mpeg_mode(struct lgs8gxx_state *priv,
	u8 serial, u8 clk_pol, u8 clk_gated)
{
	int ret = 0;
	u8 t, reg_addr;

	reg_addr = (priv->config->prod == LGS8GXX_PROD_LGS8G75) ? 0x30 : 0xC2;
	ret = lgs8gxx_read_reg(priv, reg_addr, &t);
	if (ret != 0)
		return ret;

	t &= 0xF8;
	t |= serial ? TS_SERIAL : TS_PARALLEL;
	t |= clk_pol ? TS_CLK_INVERTED : TS_CLK_NORMAL;
	t |= clk_gated ? TS_CLK_GATED : TS_CLK_FREERUN;

	ret = lgs8gxx_write_reg(priv, reg_addr, t);
	if (ret != 0)
		return ret;

	return 0;
}