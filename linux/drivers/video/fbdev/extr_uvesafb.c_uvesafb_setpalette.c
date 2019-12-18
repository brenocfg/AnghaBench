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
struct uvesafb_par {int mode_idx; int vbe_modes_cnt; scalar_t__ pmi_setpal; TYPE_1__* vbe_modes; } ;
struct uvesafb_pal_entry {int red; int green; int blue; } ;
struct TYPE_5__ {int eax; int ebx; int ecx; int edx; } ;
struct TYPE_6__ {int buf_len; TYPE_2__ regs; int /*<<< orphan*/  flags; } ;
struct uvesafb_ktask {TYPE_3__ t; struct uvesafb_pal_entry* buf; } ;
struct fb_info {struct uvesafb_par* par; } ;
struct TYPE_4__ {int mode_attr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TF_BUF_ESDI ; 
 int VBE_MODE_VGACOMPAT ; 
 int /*<<< orphan*/  dac_reg ; 
 int /*<<< orphan*/  dac_val ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int uvesafb_exec (struct uvesafb_ktask*) ; 
 int /*<<< orphan*/  uvesafb_free (struct uvesafb_ktask*) ; 
 struct uvesafb_ktask* uvesafb_prep () ; 

__attribute__((used)) static int uvesafb_setpalette(struct uvesafb_pal_entry *entries, int count,
		int start, struct fb_info *info)
{
	struct uvesafb_ktask *task;
#ifdef CONFIG_X86
	struct uvesafb_par *par = info->par;
	int i = par->mode_idx;
#endif
	int err = 0;

	/*
	 * We support palette modifications for 8 bpp modes only, so
	 * there can never be more than 256 entries.
	 */
	if (start + count > 256)
		return -EINVAL;

#ifdef CONFIG_X86
	/* Use VGA registers if mode is VGA-compatible. */
	if (i >= 0 && i < par->vbe_modes_cnt &&
	    par->vbe_modes[i].mode_attr & VBE_MODE_VGACOMPAT) {
		for (i = 0; i < count; i++) {
			outb_p(start + i,        dac_reg);
			outb_p(entries[i].red,   dac_val);
			outb_p(entries[i].green, dac_val);
			outb_p(entries[i].blue,  dac_val);
		}
	}
#ifdef CONFIG_X86_32
	else if (par->pmi_setpal) {
		__asm__ __volatile__(
		"call *(%%esi)"
		: /* no return value */
		: "a" (0x4f09),         /* EAX */
		  "b" (0),              /* EBX */
		  "c" (count),          /* ECX */
		  "d" (start),          /* EDX */
		  "D" (entries),        /* EDI */
		  "S" (&par->pmi_pal)); /* ESI */
	}
#endif /* CONFIG_X86_32 */
	else
#endif /* CONFIG_X86 */
	{
		task = uvesafb_prep();
		if (!task)
			return -ENOMEM;

		task->t.regs.eax = 0x4f09;
		task->t.regs.ebx = 0x0;
		task->t.regs.ecx = count;
		task->t.regs.edx = start;
		task->t.flags = TF_BUF_ESDI;
		task->t.buf_len = sizeof(struct uvesafb_pal_entry) * count;
		task->buf = entries;

		err = uvesafb_exec(task);
		if ((task->t.regs.eax & 0xffff) != 0x004f)
			err = 1;

		uvesafb_free(task);
	}
	return err;
}