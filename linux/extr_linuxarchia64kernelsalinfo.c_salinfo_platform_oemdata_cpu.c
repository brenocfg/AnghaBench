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
struct salinfo_platform_oemdata_parms {int /*<<< orphan*/  oemdata_size; int /*<<< orphan*/  oemdata; int /*<<< orphan*/  efi_guid; } ;

/* Variables and functions */
 long salinfo_platform_oemdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
salinfo_platform_oemdata_cpu(void *context)
{
	struct salinfo_platform_oemdata_parms *parms = context;

	return salinfo_platform_oemdata(parms->efi_guid, parms->oemdata, parms->oemdata_size);
}