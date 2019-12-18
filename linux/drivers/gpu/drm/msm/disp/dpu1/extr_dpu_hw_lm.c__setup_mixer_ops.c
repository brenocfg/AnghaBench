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
struct dpu_mdss_cfg {int /*<<< orphan*/  hwversion; } ;
struct dpu_hw_lm_ops {int /*<<< orphan*/  setup_border_color; int /*<<< orphan*/  setup_alpha_out; int /*<<< orphan*/  setup_blend_config; int /*<<< orphan*/  setup_mixer_out; } ;

/* Variables and functions */
 scalar_t__ IS_SDM670_TARGET (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SDM845_TARGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_hw_lm_setup_blend_config ; 
 int /*<<< orphan*/  dpu_hw_lm_setup_blend_config_sdm845 ; 
 int /*<<< orphan*/  dpu_hw_lm_setup_border_color ; 
 int /*<<< orphan*/  dpu_hw_lm_setup_color3 ; 
 int /*<<< orphan*/  dpu_hw_lm_setup_out ; 

__attribute__((used)) static void _setup_mixer_ops(struct dpu_mdss_cfg *m,
		struct dpu_hw_lm_ops *ops,
		unsigned long features)
{
	ops->setup_mixer_out = dpu_hw_lm_setup_out;
	if (IS_SDM845_TARGET(m->hwversion) || IS_SDM670_TARGET(m->hwversion))
		ops->setup_blend_config = dpu_hw_lm_setup_blend_config_sdm845;
	else
		ops->setup_blend_config = dpu_hw_lm_setup_blend_config;
	ops->setup_alpha_out = dpu_hw_lm_setup_color3;
	ops->setup_border_color = dpu_hw_lm_setup_border_color;
}