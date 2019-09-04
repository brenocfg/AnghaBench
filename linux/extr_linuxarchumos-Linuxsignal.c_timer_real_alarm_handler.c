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
struct uml_pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  mcontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  UM_GFP_ATOMIC ; 
 int /*<<< orphan*/  free (struct uml_pt_regs*) ; 
 int /*<<< orphan*/  get_regs_from_mc (struct uml_pt_regs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  timer_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct uml_pt_regs*) ; 
 struct uml_pt_regs* uml_kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_real_alarm_handler(mcontext_t *mc)
{
	struct uml_pt_regs *regs;

	regs = uml_kmalloc(sizeof(struct uml_pt_regs), UM_GFP_ATOMIC);
	if (!regs)
		panic("out of memory");

	if (mc != NULL)
		get_regs_from_mc(regs, mc);
	timer_handler(SIGALRM, NULL, regs);

	free(regs);
}