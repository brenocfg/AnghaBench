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
struct region {int dummy; } ;
struct b_cr_asym_mem_region_denverton {int /*<<< orphan*/  slice_asym_limit; int /*<<< orphan*/  slice_asym_base; } ;

/* Variables and functions */
 scalar_t__ DNV_ASYMSHIFT ; 
 scalar_t__ GENMASK_ULL (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ U64_LSHIFT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mk_region (char*,struct region*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void dnv_mk_region(char *name, struct region *rp, void *asym)
{
	struct b_cr_asym_mem_region_denverton *a = asym;

	mk_region(name, rp,
			  U64_LSHIFT(a->slice_asym_base, DNV_ASYMSHIFT),
			  U64_LSHIFT(a->slice_asym_limit, DNV_ASYMSHIFT) +
			  GENMASK_ULL(DNV_ASYMSHIFT - 1, 0));
}