#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ patch_id; int /*<<< orphan*/  data_code; } ;
struct microcode_amd {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_AMD64_PATCH_LEVEL ; 
 int /*<<< orphan*/  MSR_AMD64_PATCH_LOADER ; 
 int /*<<< orphan*/  native_rdmsr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  native_wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __apply_microcode_amd(struct microcode_amd *mc)
{
	u32 rev, dummy;

	native_wrmsrl(MSR_AMD64_PATCH_LOADER, (u64)(long)&mc->hdr.data_code);

	/* verify patch application was successful */
	native_rdmsr(MSR_AMD64_PATCH_LEVEL, rev, dummy);
	if (rev != mc->hdr.patch_id)
		return -1;

	return 0;
}