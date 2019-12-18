#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int montype; scalar_t__ dpms; scalar_t__ dram_size; int /*<<< orphan*/  pseudo_palette; } ;
struct TYPE_9__ {int length; } ;
struct TYPE_8__ {int length; } ;
struct TYPE_10__ {int height; int width; int /*<<< orphan*/  accel_flags; int /*<<< orphan*/  vmode; int /*<<< orphan*/  activate; scalar_t__ nonstd; TYPE_3__ red; TYPE_3__ blue; TYPE_3__ green; TYPE_2__ transp; } ;
struct TYPE_7__ {int ypanstep; int ywrapstep; int /*<<< orphan*/  accel; scalar_t__ line_length; scalar_t__ xpanstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {int flags; TYPE_4__ var; TYPE_1__ fix; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; } ;

/* Variables and functions */
 int FBINFO_DEFAULT ; 
 int FBINFO_HWACCEL_YPAN ; 
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int /*<<< orphan*/  acornfb_ops ; 
 TYPE_6__ current_par ; 
 TYPE_5__ fb_info ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void acornfb_init_fbinfo(void)
{
	static int first = 1;

	if (!first)
		return;
	first = 0;

	fb_info.fbops		= &acornfb_ops;
	fb_info.flags		= FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	fb_info.pseudo_palette	= current_par.pseudo_palette;

	strcpy(fb_info.fix.id, "Acorn");
	fb_info.fix.type	= FB_TYPE_PACKED_PIXELS;
	fb_info.fix.type_aux	= 0;
	fb_info.fix.xpanstep	= 0;
	fb_info.fix.ypanstep	= 1;
	fb_info.fix.ywrapstep	= 1;
	fb_info.fix.line_length	= 0;
	fb_info.fix.accel	= FB_ACCEL_NONE;

	/*
	 * setup initial parameters
	 */
	memset(&fb_info.var, 0, sizeof(fb_info.var));

#if defined(HAS_VIDC20)
	fb_info.var.red.length	   = 8;
	fb_info.var.transp.length  = 4;
#endif
	fb_info.var.green	   = fb_info.var.red;
	fb_info.var.blue	   = fb_info.var.red;
	fb_info.var.nonstd	   = 0;
	fb_info.var.activate	   = FB_ACTIVATE_NOW;
	fb_info.var.height	   = -1;
	fb_info.var.width	   = -1;
	fb_info.var.vmode	   = FB_VMODE_NONINTERLACED;
	fb_info.var.accel_flags	   = FB_ACCELF_TEXT;

	current_par.dram_size	   = 0;
	current_par.montype	   = -1;
	current_par.dpms	   = 0;
}