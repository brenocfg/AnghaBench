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
struct intel_uc_fw {int __status; } ;
typedef  enum intel_uc_fw_status { ____Placeholder_intel_uc_fw_status } intel_uc_fw_status ;

/* Variables and functions */

__attribute__((used)) static inline void intel_uc_fw_change_status(struct intel_uc_fw *uc_fw,
					     enum intel_uc_fw_status status)
{
	uc_fw->__status = status;
}