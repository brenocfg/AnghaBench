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
 int /*<<< orphan*/  CONFIG_KVM_AMD_SEV ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int max_sev_asid ; 

__attribute__((used)) static inline bool svm_sev_enabled(void)
{
	return IS_ENABLED(CONFIG_KVM_AMD_SEV) ? max_sev_asid : 0;
}