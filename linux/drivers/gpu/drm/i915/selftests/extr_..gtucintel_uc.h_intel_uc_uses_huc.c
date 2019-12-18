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
struct intel_uc {int /*<<< orphan*/  huc; } ;

/* Variables and functions */
 int intel_huc_is_enabled (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool intel_uc_uses_huc(struct intel_uc *uc)
{
	return intel_huc_is_enabled(&uc->huc);
}