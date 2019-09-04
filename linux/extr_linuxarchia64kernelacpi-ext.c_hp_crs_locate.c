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
struct csr_space {scalar_t__ length; scalar_t__ base; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct csr_space*) ; 
 int /*<<< orphan*/  find_csr_space ; 

__attribute__((used)) static acpi_status hp_crs_locate(acpi_handle obj, u64 *base, u64 *length)
{
	struct csr_space space = { 0, 0 };

	acpi_walk_resources(obj, METHOD_NAME__CRS, find_csr_space, &space);
	if (!space.length)
		return AE_NOT_FOUND;

	*base = space.base;
	*length = space.length;
	return AE_OK;
}