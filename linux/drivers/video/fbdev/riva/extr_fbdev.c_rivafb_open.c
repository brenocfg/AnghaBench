#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vgastate {int dummy; } ;
struct TYPE_4__ {scalar_t__ Architecture; int /*<<< orphan*/  (* LockUnlock ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int flags; } ;
struct riva_par {int /*<<< orphan*/  open_lock; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  initial_state; TYPE_1__ riva; TYPE_2__ state; } ;
struct fb_info {struct riva_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTCout (struct riva_par*,int,int) ; 
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 scalar_t__ NV_ARCH_03 ; 
 int VGA_SAVE_CMAP ; 
 int VGA_SAVE_FONTS ; 
 int VGA_SAVE_MODE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  riva_save_state (struct riva_par*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_vga (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rivafb_open(struct fb_info *info, int user)
{
	struct riva_par *par = info->par;

	NVTRACE_ENTER();
	mutex_lock(&par->open_lock);
	if (!par->ref_count) {
#ifdef CONFIG_X86
		memset(&par->state, 0, sizeof(struct vgastate));
		par->state.flags = VGA_SAVE_MODE  | VGA_SAVE_FONTS;
		/* save the DAC for Riva128 */
		if (par->riva.Architecture == NV_ARCH_03)
			par->state.flags |= VGA_SAVE_CMAP;
		save_vga(&par->state);
#endif
		/* vgaHWunlock() + riva unlock (0x7F) */
		CRTCout(par, 0x11, 0xFF);
		par->riva.LockUnlock(&par->riva, 0);
	
		riva_save_state(par, &par->initial_state);
	}
	par->ref_count++;
	mutex_unlock(&par->open_lock);
	NVTRACE_LEAVE();
	return 0;
}