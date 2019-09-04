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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DSM_REV_ID ; 
 int acpi_check_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmar_hp_guid ; 

__attribute__((used)) static inline bool dmar_detect_dsm(acpi_handle handle, int func)
{
	return acpi_check_dsm(handle, &dmar_hp_guid, DMAR_DSM_REV_ID, 1 << func);
}