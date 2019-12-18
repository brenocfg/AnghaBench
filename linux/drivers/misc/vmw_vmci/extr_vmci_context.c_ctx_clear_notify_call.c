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
struct vmci_ctx {scalar_t__ pending_datagrams; int /*<<< orphan*/  pending_doorbell_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx_clear_notify (struct vmci_ctx*) ; 
 scalar_t__ vmci_handle_arr_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctx_clear_notify_call(struct vmci_ctx *context)
{
	if (context->pending_datagrams == 0 &&
	    vmci_handle_arr_get_size(context->pending_doorbell_array) == 0)
		ctx_clear_notify(context);
}