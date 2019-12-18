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
typedef  int /*<<< orphan*/  grant_ref_t ;
typedef  int /*<<< orphan*/  domid_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_entry ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GTF_accept_transfer ; 
 TYPE_1__* gnttab_interface ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

void gnttab_grant_foreign_transfer_ref(grant_ref_t ref, domid_t domid,
				       unsigned long pfn)
{
	gnttab_interface->update_entry(ref, domid, pfn, GTF_accept_transfer);
}