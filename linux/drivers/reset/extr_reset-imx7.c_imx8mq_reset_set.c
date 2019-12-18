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
struct reset_controller_dev {int dummy; } ;
struct imx7_src {TYPE_1__* signals; } ;
struct TYPE_2__ {unsigned int bit; } ;

/* Variables and functions */
#define  IMX8MQ_RESET_MIPI_DSI_DPI_RESET_N 136 
#define  IMX8MQ_RESET_MIPI_DSI_ESC_RESET_N 135 
#define  IMX8MQ_RESET_MIPI_DSI_PCLK_RESET_N 134 
#define  IMX8MQ_RESET_MIPI_DSI_RESET_BYTE_N 133 
#define  IMX8MQ_RESET_MIPI_DSI_RESET_N 132 
#define  IMX8MQ_RESET_PCIE2_CTRL_APPS_EN 131 
#define  IMX8MQ_RESET_PCIEPHY 130 
#define  IMX8MQ_RESET_PCIEPHY2 129 
#define  IMX8MQ_RESET_PCIE_CTRL_APPS_EN 128 
 int imx7_reset_update (struct imx7_src*,unsigned long,unsigned int) ; 
 struct imx7_src* to_imx7_src (struct reset_controller_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int imx8mq_reset_set(struct reset_controller_dev *rcdev,
			    unsigned long id, bool assert)
{
	struct imx7_src *imx7src = to_imx7_src(rcdev);
	const unsigned int bit = imx7src->signals[id].bit;
	unsigned int value = assert ? bit : 0;

	switch (id) {
	case IMX8MQ_RESET_PCIEPHY:
	case IMX8MQ_RESET_PCIEPHY2: /* fallthrough */
		/*
		 * wait for more than 10us to release phy g_rst and
		 * btnrst
		 */
		if (!assert)
			udelay(10);
		break;

	case IMX8MQ_RESET_PCIE_CTRL_APPS_EN:
	case IMX8MQ_RESET_PCIE2_CTRL_APPS_EN:	/* fallthrough */
	case IMX8MQ_RESET_MIPI_DSI_PCLK_RESET_N:	/* fallthrough */
	case IMX8MQ_RESET_MIPI_DSI_ESC_RESET_N:	/* fallthrough */
	case IMX8MQ_RESET_MIPI_DSI_DPI_RESET_N:	/* fallthrough */
	case IMX8MQ_RESET_MIPI_DSI_RESET_N:	/* fallthrough */
	case IMX8MQ_RESET_MIPI_DSI_RESET_BYTE_N:	/* fallthrough */
		value = assert ? 0 : bit;
		break;
	}

	return imx7_reset_update(imx7src, id, value);
}