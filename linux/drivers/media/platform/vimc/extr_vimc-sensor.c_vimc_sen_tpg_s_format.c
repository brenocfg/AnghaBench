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
struct TYPE_2__ {int width; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  code; } ;
struct vimc_sen_device {TYPE_1__ mbus_format; int /*<<< orphan*/  tpg; } ;
struct vimc_pix_map {int bpp; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  tpg_reset_source (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpg_s_buf_height (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpg_s_bytesperline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tpg_s_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpg_s_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tpg_s_fourcc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpg_s_quantization (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpg_s_xfer_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpg_s_ycbcr_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vimc_pix_map* vimc_pix_map_by_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vimc_sen_tpg_s_format(struct vimc_sen_device *vsen)
{
	const struct vimc_pix_map *vpix =
				vimc_pix_map_by_code(vsen->mbus_format.code);

	tpg_reset_source(&vsen->tpg, vsen->mbus_format.width,
			 vsen->mbus_format.height, vsen->mbus_format.field);
	tpg_s_bytesperline(&vsen->tpg, 0, vsen->mbus_format.width * vpix->bpp);
	tpg_s_buf_height(&vsen->tpg, vsen->mbus_format.height);
	tpg_s_fourcc(&vsen->tpg, vpix->pixelformat);
	/* TODO: add support for V4L2_FIELD_ALTERNATE */
	tpg_s_field(&vsen->tpg, vsen->mbus_format.field, false);
	tpg_s_colorspace(&vsen->tpg, vsen->mbus_format.colorspace);
	tpg_s_ycbcr_enc(&vsen->tpg, vsen->mbus_format.ycbcr_enc);
	tpg_s_quantization(&vsen->tpg, vsen->mbus_format.quantization);
	tpg_s_xfer_func(&vsen->tpg, vsen->mbus_format.xfer_func);
}