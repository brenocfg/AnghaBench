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
typedef  int u32 ;
struct tpm_space {int* context_tbl; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static bool tpm2_map_to_phandle(struct tpm_space *space, void *handle)
{
	u32 vhandle = be32_to_cpup((__be32 *)handle);
	u32 phandle;
	int i;

	i = 0xFFFFFF - (vhandle & 0xFFFFFF);
	if (i >= ARRAY_SIZE(space->context_tbl) || !space->context_tbl[i])
		return false;

	phandle = space->context_tbl[i];
	*((__be32 *)handle) = cpu_to_be32(phandle);
	return true;
}