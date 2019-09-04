#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dpu_encoder_phys_vid {TYPE_2__* hw_intf; } ;
struct dpu_encoder_phys {int dummy; } ;
struct TYPE_3__ {int (* get_line_count ) (TYPE_2__*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dpu_encoder_phys_vid_is_master (struct dpu_encoder_phys*) ; 
 int stub1 (TYPE_2__*) ; 
 struct dpu_encoder_phys_vid* to_dpu_encoder_phys_vid (struct dpu_encoder_phys*) ; 

__attribute__((used)) static int dpu_encoder_phys_vid_get_line_count(
		struct dpu_encoder_phys *phys_enc)
{
	struct dpu_encoder_phys_vid *vid_enc;

	if (!phys_enc)
		return -EINVAL;

	if (!dpu_encoder_phys_vid_is_master(phys_enc))
		return -EINVAL;

	vid_enc = to_dpu_encoder_phys_vid(phys_enc);
	if (!vid_enc->hw_intf || !vid_enc->hw_intf->ops.get_line_count)
		return -EINVAL;

	return vid_enc->hw_intf->ops.get_line_count(vid_enc->hw_intf);
}