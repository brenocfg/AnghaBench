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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  int3 ;

/* Variables and functions */
 int /*<<< orphan*/ * bp_int3_addr ; 
 void* bp_int3_handler ; 
 int bp_patching_in_progress ; 
 int /*<<< orphan*/  do_sync_core ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  text_mutex ; 
 int /*<<< orphan*/  text_poke (void*,void const*,int) ; 

void *text_poke_bp(void *addr, const void *opcode, size_t len, void *handler)
{
	unsigned char int3 = 0xcc;

	bp_int3_handler = handler;
	bp_int3_addr = (u8 *)addr + sizeof(int3);
	bp_patching_in_progress = true;

	lockdep_assert_held(&text_mutex);

	/*
	 * Corresponding read barrier in int3 notifier for making sure the
	 * in_progress and handler are correctly ordered wrt. patching.
	 */
	smp_wmb();

	text_poke(addr, &int3, sizeof(int3));

	on_each_cpu(do_sync_core, NULL, 1);

	if (len - sizeof(int3) > 0) {
		/* patch all but the first byte */
		text_poke((char *)addr + sizeof(int3),
			  (const char *) opcode + sizeof(int3),
			  len - sizeof(int3));
		/*
		 * According to Intel, this core syncing is very likely
		 * not necessary and we'd be safe even without it. But
		 * better safe than sorry (plus there's not only Intel).
		 */
		on_each_cpu(do_sync_core, NULL, 1);
	}

	/* patch the first byte */
	text_poke(addr, opcode, sizeof(int3));

	on_each_cpu(do_sync_core, NULL, 1);
	/*
	 * sync_core() implies an smp_mb() and orders this store against
	 * the writing of the new instruction.
	 */
	bp_patching_in_progress = false;

	return addr;
}