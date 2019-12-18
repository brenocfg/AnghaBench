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
struct intel_uncore {int fw_domains; int /*<<< orphan*/  fw_domains_table_entries; int /*<<< orphan*/  fw_domains_table; } ;
struct intel_forcewake_range {int domains; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 struct intel_forcewake_range* BSEARCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FORCEWAKE_ALL ; 
 int /*<<< orphan*/  WARN (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_range_cmp ; 

__attribute__((used)) static enum forcewake_domains
find_fw_domain(struct intel_uncore *uncore, u32 offset)
{
	const struct intel_forcewake_range *entry;

	entry = BSEARCH(offset,
			uncore->fw_domains_table,
			uncore->fw_domains_table_entries,
			fw_range_cmp);

	if (!entry)
		return 0;

	/*
	 * The list of FW domains depends on the SKU in gen11+ so we
	 * can't determine it statically. We use FORCEWAKE_ALL and
	 * translate it here to the list of available domains.
	 */
	if (entry->domains == FORCEWAKE_ALL)
		return uncore->fw_domains;

	WARN(entry->domains & ~uncore->fw_domains,
	     "Uninitialized forcewake domain(s) 0x%x accessed at 0x%x\n",
	     entry->domains & ~uncore->fw_domains, offset);

	return entry->domains;
}