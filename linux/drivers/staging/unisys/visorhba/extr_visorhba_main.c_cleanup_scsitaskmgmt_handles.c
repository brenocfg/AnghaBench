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
struct TYPE_2__ {scalar_t__ notifyresult_handle; scalar_t__ notify_handle; } ;
struct uiscmdrsp {TYPE_1__ scsitaskmgmt; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (struct idr*,scalar_t__) ; 

__attribute__((used)) static void cleanup_scsitaskmgmt_handles(struct idr *idrtable,
					 struct uiscmdrsp *cmdrsp)
{
	if (cmdrsp->scsitaskmgmt.notify_handle)
		idr_remove(idrtable, cmdrsp->scsitaskmgmt.notify_handle);
	if (cmdrsp->scsitaskmgmt.notifyresult_handle)
		idr_remove(idrtable, cmdrsp->scsitaskmgmt.notifyresult_handle);
}