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
struct dispc_device {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DISPC_MGR_FLD_TFTDATALINES ; 
 int /*<<< orphan*/  mgr_fld_write (struct dispc_device*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dispc_mgr_set_tft_data_lines(struct dispc_device *dispc,
					 enum omap_channel channel,
					 u8 data_lines)
{
	int code;

	switch (data_lines) {
	case 12:
		code = 0;
		break;
	case 16:
		code = 1;
		break;
	case 18:
		code = 2;
		break;
	case 24:
		code = 3;
		break;
	default:
		BUG();
		return;
	}

	mgr_fld_write(dispc, channel, DISPC_MGR_FLD_TFTDATALINES, code);
}