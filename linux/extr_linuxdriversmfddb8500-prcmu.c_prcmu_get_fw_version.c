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
struct prcmu_fw_version {int dummy; } ;
struct TYPE_2__ {struct prcmu_fw_version version; scalar_t__ valid; } ;

/* Variables and functions */
 TYPE_1__ fw_info ; 

struct prcmu_fw_version *prcmu_get_fw_version(void)
{
	return fw_info.valid ? &fw_info.version : NULL;
}