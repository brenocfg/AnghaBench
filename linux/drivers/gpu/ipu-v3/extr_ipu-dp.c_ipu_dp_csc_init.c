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
struct ipu_flow {scalar_t__ base; } ;
typedef  enum ipu_color_space { ____Placeholder_ipu_color_space } ipu_color_space ;

/* Variables and functions */
 scalar_t__ DP_COM_CONF ; 
 int DP_COM_CONF_CSC_DEF_MASK ; 
 scalar_t__ DP_CSC_0 ; 
 scalar_t__ DP_CSC_1 ; 
 scalar_t__ DP_CSC_A_0 ; 
 scalar_t__ DP_CSC_A_1 ; 
 scalar_t__ DP_CSC_A_2 ; 
 scalar_t__ DP_CSC_A_3 ; 
 int IPUV3_COLORSPACE_RGB ; 
 int IPUV3_COLORSPACE_YUV ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ipu_dp_csc_init(struct ipu_flow *flow,
		enum ipu_color_space in,
		enum ipu_color_space out,
		u32 place)
{
	u32 reg;

	reg = readl(flow->base + DP_COM_CONF);
	reg &= ~DP_COM_CONF_CSC_DEF_MASK;

	if (in == out) {
		writel(reg, flow->base + DP_COM_CONF);
		return;
	}

	if (in == IPUV3_COLORSPACE_RGB && out == IPUV3_COLORSPACE_YUV) {
		writel(0x099 | (0x12d << 16), flow->base + DP_CSC_A_0);
		writel(0x03a | (0x3a9 << 16), flow->base + DP_CSC_A_1);
		writel(0x356 | (0x100 << 16), flow->base + DP_CSC_A_2);
		writel(0x100 | (0x329 << 16), flow->base + DP_CSC_A_3);
		writel(0x3d6 | (0x0000 << 16) | (2 << 30),
				flow->base + DP_CSC_0);
		writel(0x200 | (2 << 14) | (0x200 << 16) | (2 << 30),
				flow->base + DP_CSC_1);
	} else {
		writel(0x095 | (0x000 << 16), flow->base + DP_CSC_A_0);
		writel(0x0cc | (0x095 << 16), flow->base + DP_CSC_A_1);
		writel(0x3ce | (0x398 << 16), flow->base + DP_CSC_A_2);
		writel(0x095 | (0x0ff << 16), flow->base + DP_CSC_A_3);
		writel(0x000 | (0x3e42 << 16) | (1 << 30),
				flow->base + DP_CSC_0);
		writel(0x10a | (1 << 14) | (0x3dd6 << 16) | (1 << 30),
				flow->base + DP_CSC_1);
	}

	reg |= place;

	writel(reg, flow->base + DP_COM_CONF);
}