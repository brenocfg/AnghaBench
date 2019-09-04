#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mdp5_kms {int /*<<< orphan*/  cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  caps; int /*<<< orphan*/  base; int /*<<< orphan*/  count; } ;
struct TYPE_7__ {int /*<<< orphan*/  caps; int /*<<< orphan*/  base; int /*<<< orphan*/  count; } ;
struct TYPE_6__ {int /*<<< orphan*/  caps; int /*<<< orphan*/  base; int /*<<< orphan*/  count; } ;
struct TYPE_5__ {int /*<<< orphan*/  caps; int /*<<< orphan*/  base; int /*<<< orphan*/  count; } ;
struct mdp5_cfg_hw {TYPE_4__ pipe_cursor; TYPE_3__ pipe_dma; TYPE_2__ pipe_vig; TYPE_1__ pipe_rgb; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
#define  SSPP_CURSOR0 139 
#define  SSPP_CURSOR1 138 
#define  SSPP_DMA0 137 
#define  SSPP_DMA1 136 
#define  SSPP_RGB0 135 
#define  SSPP_RGB1 134 
#define  SSPP_RGB2 133 
#define  SSPP_RGB3 132 
#define  SSPP_VIG0 131 
#define  SSPP_VIG1 130 
#define  SSPP_VIG2 129 
#define  SSPP_VIG3 128 
 int construct_pipes (struct mdp5_kms*,int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdp5_cfg_hw* mdp5_cfg_get_hw_config (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwpipe_init(struct mdp5_kms *mdp5_kms)
{
	static const enum mdp5_pipe rgb_planes[] = {
			SSPP_RGB0, SSPP_RGB1, SSPP_RGB2, SSPP_RGB3,
	};
	static const enum mdp5_pipe vig_planes[] = {
			SSPP_VIG0, SSPP_VIG1, SSPP_VIG2, SSPP_VIG3,
	};
	static const enum mdp5_pipe dma_planes[] = {
			SSPP_DMA0, SSPP_DMA1,
	};
	static const enum mdp5_pipe cursor_planes[] = {
			SSPP_CURSOR0, SSPP_CURSOR1,
	};
	const struct mdp5_cfg_hw *hw_cfg;
	int ret;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);

	/* Construct RGB pipes: */
	ret = construct_pipes(mdp5_kms, hw_cfg->pipe_rgb.count, rgb_planes,
			hw_cfg->pipe_rgb.base, hw_cfg->pipe_rgb.caps);
	if (ret)
		return ret;

	/* Construct video (VIG) pipes: */
	ret = construct_pipes(mdp5_kms, hw_cfg->pipe_vig.count, vig_planes,
			hw_cfg->pipe_vig.base, hw_cfg->pipe_vig.caps);
	if (ret)
		return ret;

	/* Construct DMA pipes: */
	ret = construct_pipes(mdp5_kms, hw_cfg->pipe_dma.count, dma_planes,
			hw_cfg->pipe_dma.base, hw_cfg->pipe_dma.caps);
	if (ret)
		return ret;

	/* Construct cursor pipes: */
	ret = construct_pipes(mdp5_kms, hw_cfg->pipe_cursor.count,
			cursor_planes, hw_cfg->pipe_cursor.base,
			hw_cfg->pipe_cursor.caps);
	if (ret)
		return ret;

	return 0;
}