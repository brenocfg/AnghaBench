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
struct vmci_ctx {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx_free_ctx ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vmci_ctx_put(struct vmci_ctx *context)
{
	kref_put(&context->kref, ctx_free_ctx);
}