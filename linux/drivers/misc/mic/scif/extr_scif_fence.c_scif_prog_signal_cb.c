#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scif_cb_arg {int /*<<< orphan*/  src_dma_addr; int /*<<< orphan*/  status; TYPE_2__* ep; } ;
struct TYPE_4__ {TYPE_1__* remote_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  signal_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scif_cb_arg*) ; 

__attribute__((used)) static void scif_prog_signal_cb(void *arg)
{
	struct scif_cb_arg *cb_arg = arg;

	dma_pool_free(cb_arg->ep->remote_dev->signal_pool, cb_arg->status,
		      cb_arg->src_dma_addr);
	kfree(cb_arg);
}