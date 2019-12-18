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
struct TYPE_2__ {int /*<<< orphan*/  de_wait; } ;
struct sm750_dev {int vidmem_size; int fb_count; scalar_t__ revid; int dataflow; int pvMem; TYPE_1__ accel; int /*<<< orphan*/  hwCursor; } ;
struct lynxfb_crtc {int vidmem_size; int line_pad; int xpanstep; int ypanstep; int oScreen; int vScreen; void* channel; scalar_t__ ywrapstep; } ;
struct lynxfb_output {void* paths; int /*<<< orphan*/  proc_setBLANK; } ;
struct lynxfb_par {int /*<<< orphan*/  index; struct lynxfb_crtc crtc; struct lynxfb_output output; struct sm750_dev* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SM750LE_REVISION_ID ; 
 int /*<<< orphan*/  g_hwcursor ; 
 int /*<<< orphan*/  hw_sm750_deWait ; 
 int /*<<< orphan*/  hw_sm750_setBLANK ; 
 int /*<<< orphan*/  hw_sm750le_deWait ; 
 int /*<<< orphan*/  hw_sm750le_setBLANK ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 void* sm750_crt ; 
#define  sm750_dual_normal 131 
#define  sm750_dual_swap 130 
 void* sm750_panel ; 
 void* sm750_pnc ; 
 void* sm750_primary ; 
 void* sm750_secondary ; 
#define  sm750_simul_pri 129 
#define  sm750_simul_sec 128 

__attribute__((used)) static int sm750fb_set_drv(struct lynxfb_par *par)
{
	int ret;
	struct sm750_dev *sm750_dev;
	struct lynxfb_output *output;
	struct lynxfb_crtc *crtc;

	ret = 0;

	sm750_dev = par->dev;
	output = &par->output;
	crtc = &par->crtc;

	crtc->vidmem_size = sm750_dev->vidmem_size;
	if (sm750_dev->fb_count > 1)
		crtc->vidmem_size >>= 1;

	/* setup crtc and output member */
	sm750_dev->hwCursor = g_hwcursor;

	crtc->line_pad = 16;
	crtc->xpanstep = 8;
	crtc->ypanstep = 1;
	crtc->ywrapstep = 0;

	output->proc_setBLANK = (sm750_dev->revid == SM750LE_REVISION_ID) ?
				 hw_sm750le_setBLANK : hw_sm750_setBLANK;
	/* chip specific phase */
	sm750_dev->accel.de_wait = (sm750_dev->revid == SM750LE_REVISION_ID) ?
				    hw_sm750le_deWait : hw_sm750_deWait;
	switch (sm750_dev->dataflow) {
	case sm750_simul_pri:
		output->paths = sm750_pnc;
		crtc->channel = sm750_primary;
		crtc->oScreen = 0;
		crtc->vScreen = sm750_dev->pvMem;
		pr_info("use simul primary mode\n");
		break;
	case sm750_simul_sec:
		output->paths = sm750_pnc;
		crtc->channel = sm750_secondary;
		crtc->oScreen = 0;
		crtc->vScreen = sm750_dev->pvMem;
		break;
	case sm750_dual_normal:
		if (par->index == 0) {
			output->paths = sm750_panel;
			crtc->channel = sm750_primary;
			crtc->oScreen = 0;
			crtc->vScreen = sm750_dev->pvMem;
		} else {
			output->paths = sm750_crt;
			crtc->channel = sm750_secondary;
			/* not consider of padding stuffs for oScreen,need fix */
			crtc->oScreen = sm750_dev->vidmem_size >> 1;
			crtc->vScreen = sm750_dev->pvMem + crtc->oScreen;
		}
		break;
	case sm750_dual_swap:
		if (par->index == 0) {
			output->paths = sm750_panel;
			crtc->channel = sm750_secondary;
			crtc->oScreen = 0;
			crtc->vScreen = sm750_dev->pvMem;
		} else {
			output->paths = sm750_crt;
			crtc->channel = sm750_primary;
			/* not consider of padding stuffs for oScreen,need fix */
			crtc->oScreen = sm750_dev->vidmem_size >> 1;
			crtc->vScreen = sm750_dev->pvMem + crtc->oScreen;
		}
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}