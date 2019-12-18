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
struct msm_kms {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int mdp5_cmd_encoder_set_split_display (struct drm_encoder*,struct drm_encoder*) ; 
 int mdp5_vid_encoder_set_split_display (struct drm_encoder*,struct drm_encoder*) ; 

__attribute__((used)) static int mdp5_set_split_display(struct msm_kms *kms,
		struct drm_encoder *encoder,
		struct drm_encoder *slave_encoder,
		bool is_cmd_mode)
{
	if (is_cmd_mode)
		return mdp5_cmd_encoder_set_split_display(encoder,
							slave_encoder);
	else
		return mdp5_vid_encoder_set_split_display(encoder,
							  slave_encoder);
}