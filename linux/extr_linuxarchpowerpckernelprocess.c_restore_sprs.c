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
struct thread_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  thread_pkey_regs_restore (struct thread_struct*,struct thread_struct*) ; 

__attribute__((used)) static inline void restore_sprs(struct thread_struct *old_thread,
				struct thread_struct *new_thread)
{
#ifdef CONFIG_ALTIVEC
	if (cpu_has_feature(CPU_FTR_ALTIVEC) &&
	    old_thread->vrsave != new_thread->vrsave)
		mtspr(SPRN_VRSAVE, new_thread->vrsave);
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	if (cpu_has_feature(CPU_FTR_DSCR)) {
		u64 dscr = get_paca()->dscr_default;
		if (new_thread->dscr_inherit)
			dscr = new_thread->dscr;

		if (old_thread->dscr != dscr)
			mtspr(SPRN_DSCR, dscr);
	}

	if (cpu_has_feature(CPU_FTR_ARCH_207S)) {
		if (old_thread->bescr != new_thread->bescr)
			mtspr(SPRN_BESCR, new_thread->bescr);
		if (old_thread->ebbhr != new_thread->ebbhr)
			mtspr(SPRN_EBBHR, new_thread->ebbhr);
		if (old_thread->ebbrr != new_thread->ebbrr)
			mtspr(SPRN_EBBRR, new_thread->ebbrr);

		if (old_thread->fscr != new_thread->fscr)
			mtspr(SPRN_FSCR, new_thread->fscr);

		if (old_thread->tar != new_thread->tar)
			mtspr(SPRN_TAR, new_thread->tar);
	}

	if (cpu_has_feature(CPU_FTR_P9_TIDR) &&
	    old_thread->tidr != new_thread->tidr)
		mtspr(SPRN_TIDR, new_thread->tidr);
#endif

	thread_pkey_regs_restore(new_thread, old_thread);
}