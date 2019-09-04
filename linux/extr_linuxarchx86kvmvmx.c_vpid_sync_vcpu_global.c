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
 int /*<<< orphan*/  VMX_VPID_EXTENT_ALL_CONTEXT ; 
 int /*<<< orphan*/  __invvpid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_vmx_invvpid_global () ; 

__attribute__((used)) static inline void vpid_sync_vcpu_global(void)
{
	if (cpu_has_vmx_invvpid_global())
		__invvpid(VMX_VPID_EXTENT_ALL_CONTEXT, 0, 0);
}