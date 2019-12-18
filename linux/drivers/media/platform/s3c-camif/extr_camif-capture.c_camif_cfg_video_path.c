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
struct camif_vp {int /*<<< orphan*/  scaler; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_hw_set_flip (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_set_output_dma (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_set_scaler (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_set_target_format (struct camif_vp*) ; 
 int /*<<< orphan*/  s3c_camif_get_scaler_config (struct camif_vp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void camif_cfg_video_path(struct camif_vp *vp)
{
	WARN_ON(s3c_camif_get_scaler_config(vp, &vp->scaler));
	camif_hw_set_scaler(vp);
	camif_hw_set_flip(vp);
	camif_hw_set_target_format(vp);
	camif_hw_set_output_dma(vp);
}