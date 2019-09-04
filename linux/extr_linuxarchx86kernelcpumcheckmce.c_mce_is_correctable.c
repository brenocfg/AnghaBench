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
struct mce {scalar_t__ cpuvendor; int status; } ;

/* Variables and functions */
 int MCI_STATUS_DEFERRED ; 
 int MCI_STATUS_UC ; 
 scalar_t__ X86_VENDOR_AMD ; 

bool mce_is_correctable(struct mce *m)
{
	if (m->cpuvendor == X86_VENDOR_AMD && m->status & MCI_STATUS_DEFERRED)
		return false;

	if (m->status & MCI_STATUS_UC)
		return false;

	return true;
}