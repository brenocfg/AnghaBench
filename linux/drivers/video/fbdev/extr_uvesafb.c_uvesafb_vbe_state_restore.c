#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct uvesafb_par {int /*<<< orphan*/  vbe_state_size; } ;
struct TYPE_3__ {int eax; int ecx; int edx; } ;
struct TYPE_4__ {TYPE_1__ regs; int /*<<< orphan*/  flags; int /*<<< orphan*/  buf_len; } ;
struct uvesafb_ktask {TYPE_2__ t; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TF_BUF_ESBX ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int uvesafb_exec (struct uvesafb_ktask*) ; 
 int /*<<< orphan*/  uvesafb_free (struct uvesafb_ktask*) ; 
 struct uvesafb_ktask* uvesafb_prep () ; 

__attribute__((used)) static void uvesafb_vbe_state_restore(struct uvesafb_par *par, u8 *state_buf)
{
	struct uvesafb_ktask *task;
	int err;

	if (!state_buf)
		return;

	task = uvesafb_prep();
	if (!task)
		return;

	task->t.regs.eax = 0x4f04;
	task->t.regs.ecx = 0x000f;
	task->t.regs.edx = 0x0002;
	task->t.buf_len = par->vbe_state_size;
	task->t.flags = TF_BUF_ESBX;
	task->buf = state_buf;

	err = uvesafb_exec(task);
	if (err || (task->t.regs.eax & 0xffff) != 0x004f)
		pr_warn("VBE state restore call failed (eax=0x%x, err=%d)\n",
			task->t.regs.eax, err);

	uvesafb_free(task);
}