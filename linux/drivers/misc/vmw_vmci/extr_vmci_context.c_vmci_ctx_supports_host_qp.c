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
struct vmci_ctx {scalar_t__ user_version; } ;

/* Variables and functions */
 scalar_t__ VMCI_VERSION_HOSTQP ; 

bool vmci_ctx_supports_host_qp(struct vmci_ctx *context)
{
	return context && context->user_version >= VMCI_VERSION_HOSTQP;
}