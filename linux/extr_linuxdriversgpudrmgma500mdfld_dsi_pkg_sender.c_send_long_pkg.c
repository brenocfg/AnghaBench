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
struct mdfld_dsi_pkg_sender {int mipi_hs_gen_ctrl_reg; int mipi_hs_gen_data_reg; int mipi_lp_gen_ctrl_reg; int mipi_lp_gen_data_reg; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int FLD_VAL (int,int,int) ; 
 int /*<<< orphan*/  REG_WRITE (int,int) ; 

__attribute__((used)) static int send_long_pkg(struct mdfld_dsi_pkg_sender *sender, u8 data_type,
			u8 *data, int len, bool hs)
{
	struct drm_device *dev = sender->dev;
	u32 ctrl_reg;
	u32 data_reg;
	u32 val;
	u8 *p;
	u8 b1, b2, b3, b4;
	u8 virtual_channel = 0;
	int i;

	if (hs) {
		ctrl_reg = sender->mipi_hs_gen_ctrl_reg;
		data_reg = sender->mipi_hs_gen_data_reg;

		/* FIXME: wait_for_hs_fifos_empty(sender); */
	} else {
		ctrl_reg = sender->mipi_lp_gen_ctrl_reg;
		data_reg = sender->mipi_lp_gen_data_reg;

		/* FIXME: wait_for_lp_fifos_empty(sender); */
	}

	p = data;
	for (i = 0; i < len / 4; i++) {
		b1 = *p++;
		b2 = *p++;
		b3 = *p++;
		b4 = *p++;

		REG_WRITE(data_reg, b4 << 24 | b3 << 16 | b2 << 8 | b1);
	}

	i = len % 4;
	if (i) {
		b1 = 0; b2 = 0; b3 = 0;

		switch (i) {
		case 3:
			b1 = *p++;
			b2 = *p++;
			b3 = *p++;
			break;
		case 2:
			b1 = *p++;
			b2 = *p++;
			break;
		case 1:
			b1 = *p++;
			break;
		}

		REG_WRITE(data_reg, b3 << 16 | b2 << 8 | b1);
	}

	val = FLD_VAL(len, 23, 8) | FLD_VAL(virtual_channel, 7, 6) |
		FLD_VAL(data_type, 5, 0);

	REG_WRITE(ctrl_reg, val);

	return 0;
}