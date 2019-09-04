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
typedef  scalar_t__ u64 ;
struct sthyi_sctns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_diag (struct sthyi_sctns*) ; 
 int /*<<< orphan*/  fill_hdr (struct sthyi_sctns*) ; 
 int /*<<< orphan*/  fill_stsi (struct sthyi_sctns*) ; 
 int sthyi (scalar_t__,scalar_t__*) ; 
 scalar_t__ test_facility (int) ; 

__attribute__((used)) static int fill_dst(void *dst, u64 *rc)
{
	struct sthyi_sctns *sctns = (struct sthyi_sctns *)dst;

	/*
	 * If the facility is on, we don't want to emulate the instruction.
	 * We ask the hypervisor to provide the data.
	 */
	if (test_facility(74))
		return sthyi((u64)dst, rc);

	fill_hdr(sctns);
	fill_stsi(sctns);
	fill_diag(sctns);
	*rc = 0;
	return 0;
}