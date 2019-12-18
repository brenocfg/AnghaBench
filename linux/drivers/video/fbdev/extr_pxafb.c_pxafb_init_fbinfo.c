#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  u32 ;
struct pxafb_mach_info {int dummy; } ;
struct TYPE_5__ {int height; int width; int /*<<< orphan*/  vmode; int /*<<< orphan*/  accel_flags; int /*<<< orphan*/  activate; scalar_t__ nonstd; } ;
struct TYPE_4__ {int ypanstep; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ xpanstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int node; void* pseudo_palette; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; TYPE_2__ var; TYPE_1__ fix; } ;
struct pxafb_info {int /*<<< orphan*/  disable_done; int /*<<< orphan*/  ctrlr_lock; int /*<<< orphan*/  task; int /*<<< orphan*/  ctrlr_wait; int /*<<< orphan*/  lccr0; scalar_t__ task_state; int /*<<< orphan*/  state; TYPE_3__ fb; int /*<<< orphan*/  clk; struct pxafb_mach_info* inf; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_STARTUP ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct pxafb_info* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct pxafb_info* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCCR0_OUC ; 
 int /*<<< orphan*/  PXA_NAME ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct pxafb_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxafb_decode_mach_info (struct pxafb_info*,struct pxafb_mach_info*) ; 
 int /*<<< orphan*/  pxafb_ops ; 
 scalar_t__ pxafb_overlay_supported () ; 
 int /*<<< orphan*/  pxafb_task ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pxafb_info *pxafb_init_fbinfo(struct device *dev,
					    struct pxafb_mach_info *inf)
{
	struct pxafb_info *fbi;
	void *addr;

	/* Alloc the pxafb_info and pseudo_palette in one step */
	fbi = devm_kzalloc(dev, sizeof(struct pxafb_info) + sizeof(u32) * 16,
			   GFP_KERNEL);
	if (!fbi)
		return ERR_PTR(-ENOMEM);

	fbi->dev = dev;
	fbi->inf = inf;

	fbi->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(fbi->clk))
		return ERR_CAST(fbi->clk);

	strcpy(fbi->fb.fix.id, PXA_NAME);

	fbi->fb.fix.type	= FB_TYPE_PACKED_PIXELS;
	fbi->fb.fix.type_aux	= 0;
	fbi->fb.fix.xpanstep	= 0;
	fbi->fb.fix.ypanstep	= 1;
	fbi->fb.fix.ywrapstep	= 0;
	fbi->fb.fix.accel	= FB_ACCEL_NONE;

	fbi->fb.var.nonstd	= 0;
	fbi->fb.var.activate	= FB_ACTIVATE_NOW;
	fbi->fb.var.height	= -1;
	fbi->fb.var.width	= -1;
	fbi->fb.var.accel_flags	= FB_ACCELF_TEXT;
	fbi->fb.var.vmode	= FB_VMODE_NONINTERLACED;

	fbi->fb.fbops		= &pxafb_ops;
	fbi->fb.flags		= FBINFO_DEFAULT;
	fbi->fb.node		= -1;

	addr = fbi;
	addr = addr + sizeof(struct pxafb_info);
	fbi->fb.pseudo_palette	= addr;

	fbi->state		= C_STARTUP;
	fbi->task_state		= (u_char)-1;

	pxafb_decode_mach_info(fbi, inf);

#ifdef CONFIG_FB_PXA_OVERLAY
	/* place overlay(s) on top of base */
	if (pxafb_overlay_supported())
		fbi->lccr0 |= LCCR0_OUC;
#endif

	init_waitqueue_head(&fbi->ctrlr_wait);
	INIT_WORK(&fbi->task, pxafb_task);
	mutex_init(&fbi->ctrlr_lock);
	init_completion(&fbi->disable_done);

	return fbi;
}