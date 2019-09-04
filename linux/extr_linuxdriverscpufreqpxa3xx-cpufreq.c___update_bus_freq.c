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
typedef  int uint32_t ;
struct pxa3xx_freq_info {int /*<<< orphan*/  dmcfs; int /*<<< orphan*/  hss; int /*<<< orphan*/  sflfs; int /*<<< orphan*/  smcfs; } ;

/* Variables and functions */
 int ACCR ; 
 int ACCR_DMCFS (int /*<<< orphan*/ ) ; 
 int ACCR_DMCFS_MASK ; 
 int ACCR_HSS (int /*<<< orphan*/ ) ; 
 int ACCR_HSS_MASK ; 
 int ACCR_SFLFS (int /*<<< orphan*/ ) ; 
 int ACCR_SFLFS_MASK ; 
 int ACCR_SMCFS (int /*<<< orphan*/ ) ; 
 int ACCR_SMCFS_MASK ; 
 int ACSR ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void __update_bus_freq(struct pxa3xx_freq_info *info)
{
	uint32_t mask;
	uint32_t accr = ACCR;

	mask = ACCR_SMCFS_MASK | ACCR_SFLFS_MASK | ACCR_HSS_MASK |
		ACCR_DMCFS_MASK;

	accr &= ~mask;
	accr |= ACCR_SMCFS(info->smcfs) | ACCR_SFLFS(info->sflfs) |
		ACCR_HSS(info->hss) | ACCR_DMCFS(info->dmcfs);

	ACCR = accr;

	while ((ACSR & mask) != (accr & mask))
		cpu_relax();
}