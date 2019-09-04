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
typedef  int /*<<< orphan*/  u32 ;
struct dsi_data {TYPE_1__* data; } ;
struct TYPE_2__ {int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_COMPLEXIO_CFG1 ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG5 ; 
 int /*<<< orphan*/  DSI_PLL_STATUS ; 
 int DSI_QUIRK_REVERSE_TXCLKESC ; 
 int /*<<< orphan*/  FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dsi_print_reset_status(struct dsi_data *dsi)
{
	u32 l;
	int b0, b1, b2;

	/* A dummy read using the SCP interface to any DSIPHY register is
	 * required after DSIPHY reset to complete the reset of the DSI complex
	 * I/O. */
	l = dsi_read_reg(dsi, DSI_DSIPHY_CFG5);

	if (dsi->data->quirks & DSI_QUIRK_REVERSE_TXCLKESC) {
		b0 = 28;
		b1 = 27;
		b2 = 26;
	} else {
		b0 = 24;
		b1 = 25;
		b2 = 26;
	}

#define DSI_FLD_GET(fld, start, end)\
	FLD_GET(dsi_read_reg(dsi, DSI_##fld), start, end)

	pr_debug("DSI resets: PLL (%d) CIO (%d) PHY (%x%x%x, %d, %d, %d)\n",
		DSI_FLD_GET(PLL_STATUS, 0, 0),
		DSI_FLD_GET(COMPLEXIO_CFG1, 29, 29),
		DSI_FLD_GET(DSIPHY_CFG5, b0, b0),
		DSI_FLD_GET(DSIPHY_CFG5, b1, b1),
		DSI_FLD_GET(DSIPHY_CFG5, b2, b2),
		DSI_FLD_GET(DSIPHY_CFG5, 29, 29),
		DSI_FLD_GET(DSIPHY_CFG5, 30, 30),
		DSI_FLD_GET(DSIPHY_CFG5, 31, 31));

#undef DSI_FLD_GET
}