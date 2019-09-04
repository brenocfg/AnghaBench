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
typedef  int /*<<< orphan*/  u32 ;
struct dpu_encoder_phys_vid {TYPE_2__* hw_intf; } ;
struct dpu_encoder_phys {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* collect_misr ) (TYPE_2__*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 struct dpu_encoder_phys_vid* to_dpu_encoder_phys_vid (struct dpu_encoder_phys*) ; 

__attribute__((used)) static u32 dpu_encoder_phys_vid_collect_misr(struct dpu_encoder_phys *phys_enc)
{
	struct dpu_encoder_phys_vid *vid_enc;

	if (!phys_enc)
		return 0;
	vid_enc = to_dpu_encoder_phys_vid(phys_enc);

	return vid_enc->hw_intf && vid_enc->hw_intf->ops.collect_misr ?
		vid_enc->hw_intf->ops.collect_misr(vid_enc->hw_intf) : 0;
}