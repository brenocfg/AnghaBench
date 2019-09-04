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
typedef  unsigned long u32 ;
struct uniphier_cache_data {scalar_t__ op_base; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_SSCOLPQS ; 
 unsigned long UNIPHIER_SSCOLPQS_EF ; 
 scalar_t__ UNIPHIER_SSCOPPQSEF ; 
 unsigned long UNIPHIER_SSCOPPQSEF_FE ; 
 unsigned long UNIPHIER_SSCOPPQSEF_OE ; 
 scalar_t__ UNIPHIER_SSCOQAD ; 
 scalar_t__ UNIPHIER_SSCOQM ; 
 unsigned long UNIPHIER_SSCOQM_CE ; 
 int UNIPHIER_SSCOQM_S_IS_RANGE (unsigned long) ; 
 scalar_t__ UNIPHIER_SSCOQSZ ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 scalar_t__ unlikely (unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static void __uniphier_cache_maint_common(struct uniphier_cache_data *data,
					  unsigned long start,
					  unsigned long size,
					  u32 operation)
{
	unsigned long flags;

	/*
	 * No spin lock is necessary here because:
	 *
	 * [1] This outer cache controller is able to accept maintenance
	 * operations from multiple CPUs at a time in an SMP system; if a
	 * maintenance operation is under way and another operation is issued,
	 * the new one is stored in the queue.  The controller performs one
	 * operation after another.  If the queue is full, the status register,
	 * UNIPHIER_SSCOPPQSEF, indicates that the queue registration has
	 * failed.  The status registers, UNIPHIER_{SSCOPPQSEF, SSCOLPQS}, have
	 * different instances for each CPU, i.e. each CPU can track the status
	 * of the maintenance operations triggered by itself.
	 *
	 * [2] The cache command registers, UNIPHIER_{SSCOQM, SSCOQAD, SSCOQSZ,
	 * SSCOQWN}, are shared between multiple CPUs, but the hardware still
	 * guarantees the registration sequence is atomic; the write access to
	 * them are arbitrated by the hardware.  The first accessor to the
	 * register, UNIPHIER_SSCOQM, holds the access right and it is released
	 * by reading the status register, UNIPHIER_SSCOPPQSEF.  While one CPU
	 * is holding the access right, other CPUs fail to register operations.
	 * One CPU should not hold the access right for a long time, so local
	 * IRQs should be disabled while the following sequence.
	 */
	local_irq_save(flags);

	/* clear the complete notification flag */
	writel_relaxed(UNIPHIER_SSCOLPQS_EF, data->op_base + UNIPHIER_SSCOLPQS);

	do {
		/* set cache operation */
		writel_relaxed(UNIPHIER_SSCOQM_CE | operation,
			       data->op_base + UNIPHIER_SSCOQM);

		/* set address range if needed */
		if (likely(UNIPHIER_SSCOQM_S_IS_RANGE(operation))) {
			writel_relaxed(start, data->op_base + UNIPHIER_SSCOQAD);
			writel_relaxed(size, data->op_base + UNIPHIER_SSCOQSZ);
		}
	} while (unlikely(readl_relaxed(data->op_base + UNIPHIER_SSCOPPQSEF) &
			  (UNIPHIER_SSCOPPQSEF_FE | UNIPHIER_SSCOPPQSEF_OE)));

	/* wait until the operation is completed */
	while (likely(readl_relaxed(data->op_base + UNIPHIER_SSCOLPQS) !=
		      UNIPHIER_SSCOLPQS_EF))
		cpu_relax();

	local_irq_restore(flags);
}