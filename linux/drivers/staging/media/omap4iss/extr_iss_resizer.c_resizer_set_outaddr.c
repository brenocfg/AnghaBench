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
typedef  int u32 ;
struct v4l2_mbus_framefmt {scalar_t__ code; int height; } ;
struct TYPE_2__ {int bpl_value; } ;
struct iss_resizer_device {TYPE_1__ video_out; struct v4l2_mbus_framefmt* formats; } ;
struct iss_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_UYVY8_1X16 ; 
 scalar_t__ MEDIA_BUS_FMT_YUYV8_1_5X8 ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_RESIZER ; 
 size_t RESIZER_PAD_SINK ; 
 size_t RESIZER_PAD_SOURCE_MEM ; 
 int /*<<< orphan*/  RZA_SDR_C_BAD_H ; 
 int /*<<< orphan*/  RZA_SDR_C_BAD_L ; 
 int /*<<< orphan*/  RZA_SDR_C_SAD_H ; 
 int /*<<< orphan*/  RZA_SDR_C_SAD_L ; 
 int /*<<< orphan*/  RZA_SDR_Y_BAD_H ; 
 int /*<<< orphan*/  RZA_SDR_Y_BAD_L ; 
 int /*<<< orphan*/  RZA_SDR_Y_SAD_H ; 
 int /*<<< orphan*/  RZA_SDR_Y_SAD_L ; 
 int /*<<< orphan*/  iss_reg_write (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct iss_device* to_iss_device (struct iss_resizer_device*) ; 

__attribute__((used)) static void resizer_set_outaddr(struct iss_resizer_device *resizer, u32 addr)
{
	struct iss_device *iss = to_iss_device(resizer);
	struct v4l2_mbus_framefmt *informat, *outformat;

	informat = &resizer->formats[RESIZER_PAD_SINK];
	outformat = &resizer->formats[RESIZER_PAD_SOURCE_MEM];

	/* Save address split in Base Address H & L */
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_BAD_H,
		      (addr >> 16) & 0xffff);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_BAD_L,
		      addr & 0xffff);

	/* SAD = BAD */
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_SAD_H,
		      (addr >> 16) & 0xffff);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_Y_SAD_L,
		      addr & 0xffff);

	/* Program UV buffer address... Hardcoded to be contiguous! */
	if ((informat->code == MEDIA_BUS_FMT_UYVY8_1X16) &&
	    (outformat->code == MEDIA_BUS_FMT_YUYV8_1_5X8)) {
		u32 c_addr = addr + resizer->video_out.bpl_value
			   * outformat->height;

		/* Ensure Y_BAD_L[6:0] = C_BAD_L[6:0]*/
		if ((c_addr ^ addr) & 0x7f) {
			c_addr &= ~0x7f;
			c_addr += 0x80;
			c_addr |= addr & 0x7f;
		}

		/* Save address split in Base Address H & L */
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_BAD_H,
			      (c_addr >> 16) & 0xffff);
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_BAD_L,
			      c_addr & 0xffff);

		/* SAD = BAD */
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_SAD_H,
			      (c_addr >> 16) & 0xffff);
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_RESIZER, RZA_SDR_C_SAD_L,
			      c_addr & 0xffff);
	}
}