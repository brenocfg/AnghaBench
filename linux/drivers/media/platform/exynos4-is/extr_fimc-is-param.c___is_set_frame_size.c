#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct isp_param {TYPE_2__ otf_output; TYPE_1__ otf_input; } ;
struct fimc_is {unsigned int config_index; TYPE_6__* config; } ;
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct fd_param {TYPE_5__ otf_input; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drc_param {TYPE_4__ otf_output; TYPE_3__ otf_input; } ;
struct TYPE_12__ {int /*<<< orphan*/ * p_region_index; struct fd_param fd; struct drc_param drc; struct isp_param isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARAM_DRC_OTF_INPUT ; 
 int /*<<< orphan*/  PARAM_DRC_OTF_OUTPUT ; 
 int /*<<< orphan*/  PARAM_FD_OTF_INPUT ; 
 int /*<<< orphan*/  PARAM_ISP_OTF_INPUT ; 
 int /*<<< orphan*/  PARAM_ISP_OTF_OUTPUT ; 
 int /*<<< orphan*/  fimc_is_set_param_bit (struct fimc_is*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __is_set_frame_size(struct fimc_is *is, struct v4l2_mbus_framefmt *mf)
{
	unsigned int index = is->config_index;
	struct isp_param *isp;
	struct drc_param *drc;
	struct fd_param *fd;

	isp = &is->config[index].isp;
	drc = &is->config[index].drc;
	fd = &is->config[index].fd;

	/* Update isp size info (OTF only) */
	isp->otf_input.width = mf->width;
	isp->otf_input.height = mf->height;
	isp->otf_output.width = mf->width;
	isp->otf_output.height = mf->height;
	/* Update drc size info (OTF only) */
	drc->otf_input.width = mf->width;
	drc->otf_input.height = mf->height;
	drc->otf_output.width = mf->width;
	drc->otf_output.height = mf->height;
	/* Update fd size info (OTF only) */
	fd->otf_input.width = mf->width;
	fd->otf_input.height = mf->height;

	if (test_bit(PARAM_ISP_OTF_INPUT,
		      &is->config[index].p_region_index[0]))
		return;

	/* Update field */
	fimc_is_set_param_bit(is, PARAM_ISP_OTF_INPUT);
	fimc_is_set_param_bit(is, PARAM_ISP_OTF_OUTPUT);
	fimc_is_set_param_bit(is, PARAM_DRC_OTF_INPUT);
	fimc_is_set_param_bit(is, PARAM_DRC_OTF_OUTPUT);
	fimc_is_set_param_bit(is, PARAM_FD_OTF_INPUT);
}