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
struct TYPE_2__ {int (* get_line_count ) (struct dpu_hw_pingpong*) ;} ;
struct dpu_hw_pingpong {TYPE_1__ ops; } ;
struct dpu_encoder_phys {struct dpu_hw_pingpong* hw_pp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_is_master (struct dpu_encoder_phys*) ; 
 int stub1 (struct dpu_hw_pingpong*) ; 

__attribute__((used)) static int dpu_encoder_phys_cmd_get_line_count(
		struct dpu_encoder_phys *phys_enc)
{
	struct dpu_hw_pingpong *hw_pp;

	if (!phys_enc || !phys_enc->hw_pp)
		return -EINVAL;

	if (!dpu_encoder_phys_cmd_is_master(phys_enc))
		return -EINVAL;

	hw_pp = phys_enc->hw_pp;
	if (!hw_pp->ops.get_line_count)
		return -EINVAL;

	return hw_pp->ops.get_line_count(hw_pp);
}