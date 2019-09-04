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

/* Variables and functions */
 unsigned long TX39_CONF_ICE ; 
 int /*<<< orphan*/  TX39_STOP_STREAMING () ; 
 unsigned long dcache_size ; 
 unsigned long icache_size ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  protected_blast_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  protected_blast_icache_range (unsigned long,unsigned long) ; 
 unsigned long read_c0_conf () ; 
 int /*<<< orphan*/  tx39_blast_dcache () ; 
 int /*<<< orphan*/  tx39_blast_icache () ; 
 int /*<<< orphan*/  write_c0_conf (unsigned long) ; 

__attribute__((used)) static void tx39_flush_icache_range(unsigned long start, unsigned long end)
{
	if (end - start > dcache_size)
		tx39_blast_dcache();
	else
		protected_blast_dcache_range(start, end);

	if (end - start > icache_size)
		tx39_blast_icache();
	else {
		unsigned long flags, config;
		/* disable icache (set ICE#) */
		local_irq_save(flags);
		config = read_c0_conf();
		write_c0_conf(config & ~TX39_CONF_ICE);
		TX39_STOP_STREAMING();
		protected_blast_icache_range(start, end);
		write_c0_conf(config);
		local_irq_restore(flags);
	}
}