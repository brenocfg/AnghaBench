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
struct vmci_ctx {int* notify; } ;

/* Variables and functions */

__attribute__((used)) static void ctx_clear_notify(struct vmci_ctx *context)
{
	*context->notify = false;
}