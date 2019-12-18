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
struct dwbc {int dummy; } ;
struct dcn20_dwbc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNV_FRAME_CAPTURE_EN ; 
 int /*<<< orphan*/  CNV_MODE ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct dcn20_dwbc* TO_DCN20_DWBC (struct dwbc*) ; 
 int /*<<< orphan*/  WB_ENABLE ; 

bool dwb2_is_enabled(struct dwbc *dwbc)
{
	struct dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	unsigned int wb_enabled = 0;
	unsigned int cnv_frame_capture_en = 0;

	REG_GET(WB_ENABLE, WB_ENABLE, &wb_enabled);
	REG_GET(CNV_MODE, CNV_FRAME_CAPTURE_EN, &cnv_frame_capture_en);

	return ((wb_enabled != 0) && (cnv_frame_capture_en != 0));
}