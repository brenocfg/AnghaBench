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
struct uvesafb_par {scalar_t__ ypan; scalar_t__ pmi_setpal; int /*<<< orphan*/  nocrtc; } ;
struct uvesafb_ktask {int dummy; } ;
struct fb_info {int /*<<< orphan*/  modelist; struct uvesafb_par* par; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int _PAGE_NX ; 
 int __supported_pte_mask ; 
 int /*<<< orphan*/  nocrtc ; 
 scalar_t__ pmi_setpal ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  uvesafb_free (struct uvesafb_ktask*) ; 
 struct uvesafb_ktask* uvesafb_prep () ; 
 int uvesafb_vbe_getinfo (struct uvesafb_ktask*,struct uvesafb_par*) ; 
 int uvesafb_vbe_getmodes (struct uvesafb_ktask*,struct uvesafb_par*) ; 
 int /*<<< orphan*/  uvesafb_vbe_getmonspecs (struct uvesafb_ktask*,struct fb_info*) ; 
 int /*<<< orphan*/  uvesafb_vbe_getpmi (struct uvesafb_ktask*,struct uvesafb_par*) ; 
 int /*<<< orphan*/  uvesafb_vbe_getstatesize (struct uvesafb_ktask*,struct uvesafb_par*) ; 
 scalar_t__ ypan ; 

__attribute__((used)) static int uvesafb_vbe_init(struct fb_info *info)
{
	struct uvesafb_ktask *task = NULL;
	struct uvesafb_par *par = info->par;
	int err;

	task = uvesafb_prep();
	if (!task)
		return -ENOMEM;

	err = uvesafb_vbe_getinfo(task, par);
	if (err)
		goto out;

	err = uvesafb_vbe_getmodes(task, par);
	if (err)
		goto out;

	par->nocrtc = nocrtc;
#ifdef CONFIG_X86_32
	par->pmi_setpal = pmi_setpal;
	par->ypan = ypan;

	if (par->pmi_setpal || par->ypan) {
		if (__supported_pte_mask & _PAGE_NX) {
			par->pmi_setpal = par->ypan = 0;
			pr_warn("NX protection is active, better not use the PMI\n");
		} else {
			uvesafb_vbe_getpmi(task, par);
		}
	}
#else
	/* The protected mode interface is not available on non-x86. */
	par->pmi_setpal = par->ypan = 0;
#endif

	INIT_LIST_HEAD(&info->modelist);
	uvesafb_vbe_getmonspecs(task, info);
	uvesafb_vbe_getstatesize(task, par);

out:	uvesafb_free(task);
	return err;
}