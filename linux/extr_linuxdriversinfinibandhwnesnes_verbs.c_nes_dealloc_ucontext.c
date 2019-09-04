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
struct nes_ucontext {int /*<<< orphan*/  usecnt; } ;
struct ib_ucontext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nes_ucontext*) ; 
 struct nes_ucontext* to_nesucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int nes_dealloc_ucontext(struct ib_ucontext *context)
{
	/* struct nes_vnic *nesvnic = to_nesvnic(context->device); */
	/* struct nes_device *nesdev = nesvnic->nesdev; */
	struct nes_ucontext *nes_ucontext = to_nesucontext(context);

	if (!atomic_dec_and_test(&nes_ucontext->usecnt))
	  return 0;
	kfree(nes_ucontext);
	return 0;
}