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
struct tss_struct {int /*<<< orphan*/  io_bitmap; } ;
struct thread_struct {int /*<<< orphan*/  io_bitmap_max; int /*<<< orphan*/  io_bitmap_ptr; } ;

/* Variables and functions */
 unsigned long _TIF_IO_BITMAP ; 
 int /*<<< orphan*/  cpu_tss_rw ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_tss_limit () ; 
 struct tss_struct* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void switch_to_bitmap(struct thread_struct *prev,
				    struct thread_struct *next,
				    unsigned long tifp, unsigned long tifn)
{
	struct tss_struct *tss = this_cpu_ptr(&cpu_tss_rw);

	if (tifn & _TIF_IO_BITMAP) {
		/*
		 * Copy the relevant range of the IO bitmap.
		 * Normally this is 128 bytes or less:
		 */
		memcpy(tss->io_bitmap, next->io_bitmap_ptr,
		       max(prev->io_bitmap_max, next->io_bitmap_max));
		/*
		 * Make sure that the TSS limit is correct for the CPU
		 * to notice the IO bitmap.
		 */
		refresh_tss_limit();
	} else if (tifp & _TIF_IO_BITMAP) {
		/*
		 * Clear any possible leftover bits:
		 */
		memset(tss->io_bitmap, 0xff, prev->io_bitmap_max);
	}
}