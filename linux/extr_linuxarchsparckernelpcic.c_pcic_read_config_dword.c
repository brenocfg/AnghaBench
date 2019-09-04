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
typedef  int /*<<< orphan*/  u32 ;
struct linux_pcic {scalar_t__ pcic_config_space_data; int /*<<< orphan*/  pcic_config_space_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CMD (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  nop () ; 
 struct linux_pcic pcic0 ; 
 int pcic_speculative ; 
 scalar_t__ pcic_trapped ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcic_read_config_dword(unsigned int busno, unsigned int devfn,
    int where, u32 *value)
{
	struct linux_pcic *pcic;
	unsigned long flags;

	pcic = &pcic0;

	local_irq_save(flags);
#if 0 /* does not fail here */
	pcic_speculative = 1;
	pcic_trapped = 0;
#endif
	writel(CONFIG_CMD(busno, devfn, where), pcic->pcic_config_space_addr);
#if 0 /* does not fail here */
	nop();
	if (pcic_trapped) {
		local_irq_restore(flags);
		*value = ~0;
		return 0;
	}
#endif
	pcic_speculative = 2;
	pcic_trapped = 0;
	*value = readl(pcic->pcic_config_space_data + (where&4));
	nop();
	if (pcic_trapped) {
		pcic_speculative = 0;
		local_irq_restore(flags);
		*value = ~0;
		return 0;
	}
	pcic_speculative = 0;
	local_irq_restore(flags);
	return 0;
}