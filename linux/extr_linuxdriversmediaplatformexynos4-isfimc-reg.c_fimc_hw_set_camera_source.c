#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {int /*<<< orphan*/  code; } ;
struct TYPE_8__ {int /*<<< orphan*/  vdev; } ;
struct fimc_vid_cap {TYPE_3__ ci_fmt; TYPE_2__ ve; TYPE_1__* ctx; } ;
struct fimc_source_info {int fimc_bus_type; } ;
struct fimc_frame {int o_width; int o_height; TYPE_4__* fmt; } ;
struct fimc_dev {scalar_t__ regs; struct fimc_vid_cap vid_cap; } ;
struct TYPE_11__ {int cisrcfmt; int bus_width; int /*<<< orphan*/  pixelcode; } ;
struct TYPE_10__ {int /*<<< orphan*/  color; } ;
struct TYPE_7__ {struct fimc_frame s_frame; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 int EINVAL ; 
#define  FIMC_BUS_TYPE_ISP_WRITEBACK 131 
#define  FIMC_BUS_TYPE_ITU_601 130 
#define  FIMC_BUS_TYPE_ITU_656 129 
#define  FIMC_BUS_TYPE_MIPI_CSI2 128 
 scalar_t__ FIMC_REG_CISRCFMT ; 
 int FIMC_REG_CISRCFMT_ITU601_16BIT ; 
 int FIMC_REG_CISRCFMT_ITU601_8BIT ; 
 int /*<<< orphan*/  fimc_fmt_is_user_defined (int /*<<< orphan*/ ) ; 
 TYPE_5__* pix_desc ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int fimc_hw_set_camera_source(struct fimc_dev *fimc,
			      struct fimc_source_info *source)
{
	struct fimc_vid_cap *vc = &fimc->vid_cap;
	struct fimc_frame *f = &vc->ctx->s_frame;
	u32 bus_width, cfg = 0;
	int i;

	switch (source->fimc_bus_type) {
	case FIMC_BUS_TYPE_ITU_601:
	case FIMC_BUS_TYPE_ITU_656:
		for (i = 0; i < ARRAY_SIZE(pix_desc); i++) {
			if (vc->ci_fmt.code == pix_desc[i].pixelcode) {
				cfg = pix_desc[i].cisrcfmt;
				bus_width = pix_desc[i].bus_width;
				break;
			}
		}

		if (i == ARRAY_SIZE(pix_desc)) {
			v4l2_err(&vc->ve.vdev,
				 "Camera color format not supported: %d\n",
				 vc->ci_fmt.code);
			return -EINVAL;
		}

		if (source->fimc_bus_type == FIMC_BUS_TYPE_ITU_601) {
			if (bus_width == 8)
				cfg |= FIMC_REG_CISRCFMT_ITU601_8BIT;
			else if (bus_width == 16)
				cfg |= FIMC_REG_CISRCFMT_ITU601_16BIT;
		} /* else defaults to ITU-R BT.656 8-bit */
		break;
	case FIMC_BUS_TYPE_MIPI_CSI2:
		if (fimc_fmt_is_user_defined(f->fmt->color))
			cfg |= FIMC_REG_CISRCFMT_ITU601_8BIT;
		break;
	default:
	case FIMC_BUS_TYPE_ISP_WRITEBACK:
		/* Anything to do here ? */
		break;
	}

	cfg |= (f->o_width << 16) | f->o_height;
	writel(cfg, fimc->regs + FIMC_REG_CISRCFMT);
	return 0;
}