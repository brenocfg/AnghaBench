#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smiapp_sensor {int /*<<< orphan*/ * limits; TYPE_1__* src; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_pix_clk_freq_hz; int /*<<< orphan*/  min_pix_clk_freq_hz; int /*<<< orphan*/  max_sys_clk_freq_hz; int /*<<< orphan*/  min_sys_clk_freq_hz; int /*<<< orphan*/  max_pix_clk_div; int /*<<< orphan*/  min_pix_clk_div; int /*<<< orphan*/  max_sys_clk_div; int /*<<< orphan*/  min_sys_clk_div; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_pix_clk_freq_hz; int /*<<< orphan*/  min_pix_clk_freq_hz; int /*<<< orphan*/  max_sys_clk_freq_hz; int /*<<< orphan*/  min_sys_clk_freq_hz; int /*<<< orphan*/  max_pix_clk_div; int /*<<< orphan*/  min_pix_clk_div; int /*<<< orphan*/  max_sys_clk_div; int /*<<< orphan*/  min_sys_clk_div; } ;
struct smiapp_pll_limits {int /*<<< orphan*/  min_line_length_pck; int /*<<< orphan*/  min_line_length_pck_bin; TYPE_3__ vt; TYPE_2__ op; int /*<<< orphan*/  max_pll_op_freq_hz; int /*<<< orphan*/  min_pll_op_freq_hz; int /*<<< orphan*/  max_pll_multiplier; int /*<<< orphan*/  min_pll_multiplier; int /*<<< orphan*/  max_pll_ip_freq_hz; int /*<<< orphan*/  min_pll_ip_freq_hz; int /*<<< orphan*/  max_pre_pll_clk_div; int /*<<< orphan*/  min_pre_pll_clk_div; } ;
struct smiapp_pll {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 size_t SMIAPP_LIMIT_MAX_OP_PIX_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MAX_OP_PIX_CLK_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MAX_OP_SYS_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MAX_OP_SYS_CLK_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MAX_PLL_IP_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MAX_PLL_MULTIPLIER ; 
 size_t SMIAPP_LIMIT_MAX_PLL_OP_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MAX_PRE_PLL_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MAX_VT_PIX_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MAX_VT_PIX_CLK_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MAX_VT_SYS_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MAX_VT_SYS_CLK_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MIN_LINE_LENGTH_PCK ; 
 size_t SMIAPP_LIMIT_MIN_LINE_LENGTH_PCK_BIN ; 
 size_t SMIAPP_LIMIT_MIN_OP_PIX_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MIN_OP_PIX_CLK_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MIN_OP_SYS_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MIN_OP_SYS_CLK_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MIN_PLL_IP_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MIN_PLL_MULTIPLIER ; 
 size_t SMIAPP_LIMIT_MIN_PLL_OP_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MIN_PRE_PLL_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MIN_VT_PIX_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MIN_VT_PIX_CLK_FREQ_HZ ; 
 size_t SMIAPP_LIMIT_MIN_VT_SYS_CLK_DIV ; 
 size_t SMIAPP_LIMIT_MIN_VT_SYS_CLK_FREQ_HZ ; 
 int smiapp_pll_calculate (int /*<<< orphan*/ *,struct smiapp_pll_limits*,struct smiapp_pll*) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smiapp_pll_try(struct smiapp_sensor *sensor,
			  struct smiapp_pll *pll)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	struct smiapp_pll_limits lim = {
		.min_pre_pll_clk_div = sensor->limits[SMIAPP_LIMIT_MIN_PRE_PLL_CLK_DIV],
		.max_pre_pll_clk_div = sensor->limits[SMIAPP_LIMIT_MAX_PRE_PLL_CLK_DIV],
		.min_pll_ip_freq_hz = sensor->limits[SMIAPP_LIMIT_MIN_PLL_IP_FREQ_HZ],
		.max_pll_ip_freq_hz = sensor->limits[SMIAPP_LIMIT_MAX_PLL_IP_FREQ_HZ],
		.min_pll_multiplier = sensor->limits[SMIAPP_LIMIT_MIN_PLL_MULTIPLIER],
		.max_pll_multiplier = sensor->limits[SMIAPP_LIMIT_MAX_PLL_MULTIPLIER],
		.min_pll_op_freq_hz = sensor->limits[SMIAPP_LIMIT_MIN_PLL_OP_FREQ_HZ],
		.max_pll_op_freq_hz = sensor->limits[SMIAPP_LIMIT_MAX_PLL_OP_FREQ_HZ],

		.op.min_sys_clk_div = sensor->limits[SMIAPP_LIMIT_MIN_OP_SYS_CLK_DIV],
		.op.max_sys_clk_div = sensor->limits[SMIAPP_LIMIT_MAX_OP_SYS_CLK_DIV],
		.op.min_pix_clk_div = sensor->limits[SMIAPP_LIMIT_MIN_OP_PIX_CLK_DIV],
		.op.max_pix_clk_div = sensor->limits[SMIAPP_LIMIT_MAX_OP_PIX_CLK_DIV],
		.op.min_sys_clk_freq_hz = sensor->limits[SMIAPP_LIMIT_MIN_OP_SYS_CLK_FREQ_HZ],
		.op.max_sys_clk_freq_hz = sensor->limits[SMIAPP_LIMIT_MAX_OP_SYS_CLK_FREQ_HZ],
		.op.min_pix_clk_freq_hz = sensor->limits[SMIAPP_LIMIT_MIN_OP_PIX_CLK_FREQ_HZ],
		.op.max_pix_clk_freq_hz = sensor->limits[SMIAPP_LIMIT_MAX_OP_PIX_CLK_FREQ_HZ],

		.vt.min_sys_clk_div = sensor->limits[SMIAPP_LIMIT_MIN_VT_SYS_CLK_DIV],
		.vt.max_sys_clk_div = sensor->limits[SMIAPP_LIMIT_MAX_VT_SYS_CLK_DIV],
		.vt.min_pix_clk_div = sensor->limits[SMIAPP_LIMIT_MIN_VT_PIX_CLK_DIV],
		.vt.max_pix_clk_div = sensor->limits[SMIAPP_LIMIT_MAX_VT_PIX_CLK_DIV],
		.vt.min_sys_clk_freq_hz = sensor->limits[SMIAPP_LIMIT_MIN_VT_SYS_CLK_FREQ_HZ],
		.vt.max_sys_clk_freq_hz = sensor->limits[SMIAPP_LIMIT_MAX_VT_SYS_CLK_FREQ_HZ],
		.vt.min_pix_clk_freq_hz = sensor->limits[SMIAPP_LIMIT_MIN_VT_PIX_CLK_FREQ_HZ],
		.vt.max_pix_clk_freq_hz = sensor->limits[SMIAPP_LIMIT_MAX_VT_PIX_CLK_FREQ_HZ],

		.min_line_length_pck_bin = sensor->limits[SMIAPP_LIMIT_MIN_LINE_LENGTH_PCK_BIN],
		.min_line_length_pck = sensor->limits[SMIAPP_LIMIT_MIN_LINE_LENGTH_PCK],
	};

	return smiapp_pll_calculate(&client->dev, &lim, pll);
}