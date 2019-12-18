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
struct usbctlx_rmem_completor {int /*<<< orphan*/  len; TYPE_1__* rmemresp; int /*<<< orphan*/  data; } ;
struct usbctlx_completor {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  frmlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbctlx_rmem_completor_fn(struct usbctlx_completor *head)
{
	struct usbctlx_rmem_completor *complete =
		(struct usbctlx_rmem_completor *)head;

	pr_debug("rmemresp:len=%d\n", complete->rmemresp->frmlen);
	memcpy(complete->data, complete->rmemresp->data, complete->len);
	return 0;
}