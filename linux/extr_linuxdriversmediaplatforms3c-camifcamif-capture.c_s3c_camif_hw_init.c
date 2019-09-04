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
struct s3c_camif_variant {scalar_t__ ip_revision; scalar_t__ has_img_effect; } ;
struct camif_vp {int /*<<< orphan*/  state; int /*<<< orphan*/ * out_fmt; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sd; } ;
struct camif_dev {int /*<<< orphan*/  colorfx_cb; int /*<<< orphan*/  colorfx_cr; int /*<<< orphan*/  colorfx; int /*<<< orphan*/  test_pattern; TYPE_1__ sensor; struct s3c_camif_variant* variant; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ S3C244X_CAMIF_IP_REV ; 
 scalar_t__ S3C6410_CAMIF_IP_REV ; 
 int /*<<< orphan*/  ST_VP_CONFIG ; 
 int /*<<< orphan*/  camif_cfg_video_path (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_clear_fifo_overflow (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_set_camera_bus (struct camif_dev*) ; 
 int /*<<< orphan*/  camif_hw_set_camera_crop (struct camif_dev*) ; 
 int /*<<< orphan*/  camif_hw_set_effect (struct camif_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_hw_set_input_path (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_set_source_format (struct camif_dev*) ; 
 int /*<<< orphan*/  camif_hw_set_test_pattern (struct camif_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c_camif_hw_init(struct camif_dev *camif, struct camif_vp *vp)
{
	const struct s3c_camif_variant *variant = camif->variant;

	if (camif->sensor.sd == NULL || vp->out_fmt == NULL)
		return -EINVAL;

	if (variant->ip_revision == S3C244X_CAMIF_IP_REV)
		camif_hw_clear_fifo_overflow(vp);
	camif_hw_set_camera_bus(camif);
	camif_hw_set_source_format(camif);
	camif_hw_set_camera_crop(camif);
	camif_hw_set_test_pattern(camif, camif->test_pattern);
	if (variant->has_img_effect)
		camif_hw_set_effect(camif, camif->colorfx,
				camif->colorfx_cr, camif->colorfx_cb);
	if (variant->ip_revision == S3C6410_CAMIF_IP_REV)
		camif_hw_set_input_path(vp);
	camif_cfg_video_path(vp);
	vp->state &= ~ST_VP_CONFIG;

	return 0;
}