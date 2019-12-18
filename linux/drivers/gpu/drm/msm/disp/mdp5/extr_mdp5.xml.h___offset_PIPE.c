#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;
struct TYPE_9__ {int /*<<< orphan*/ * base; } ;
struct TYPE_8__ {int /*<<< orphan*/ * base; } ;
struct TYPE_7__ {int /*<<< orphan*/ * base; } ;
struct TYPE_6__ {int /*<<< orphan*/ * base; } ;
struct TYPE_10__ {TYPE_4__ pipe_cursor; TYPE_3__ pipe_rgb; TYPE_2__ pipe_vig; TYPE_1__ pipe_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_IDX (int) ; 
#define  SSPP_CURSOR0 140 
#define  SSPP_CURSOR1 139 
#define  SSPP_DMA0 138 
#define  SSPP_DMA1 137 
#define  SSPP_NONE 136 
#define  SSPP_RGB0 135 
#define  SSPP_RGB1 134 
#define  SSPP_RGB2 133 
#define  SSPP_RGB3 132 
#define  SSPP_VIG0 131 
#define  SSPP_VIG1 130 
#define  SSPP_VIG2 129 
#define  SSPP_VIG3 128 
 TYPE_5__* mdp5_cfg ; 

__attribute__((used)) static inline uint32_t __offset_PIPE(enum mdp5_pipe idx)
{
	switch (idx) {
		case SSPP_NONE: return (INVALID_IDX(idx));
		case SSPP_VIG0: return (mdp5_cfg->pipe_vig.base[0]);
		case SSPP_VIG1: return (mdp5_cfg->pipe_vig.base[1]);
		case SSPP_VIG2: return (mdp5_cfg->pipe_vig.base[2]);
		case SSPP_RGB0: return (mdp5_cfg->pipe_rgb.base[0]);
		case SSPP_RGB1: return (mdp5_cfg->pipe_rgb.base[1]);
		case SSPP_RGB2: return (mdp5_cfg->pipe_rgb.base[2]);
		case SSPP_DMA0: return (mdp5_cfg->pipe_dma.base[0]);
		case SSPP_DMA1: return (mdp5_cfg->pipe_dma.base[1]);
		case SSPP_VIG3: return (mdp5_cfg->pipe_vig.base[3]);
		case SSPP_RGB3: return (mdp5_cfg->pipe_rgb.base[3]);
		case SSPP_CURSOR0: return (mdp5_cfg->pipe_cursor.base[0]);
		case SSPP_CURSOR1: return (mdp5_cfg->pipe_cursor.base[1]);
		default: return INVALID_IDX(idx);
	}
}