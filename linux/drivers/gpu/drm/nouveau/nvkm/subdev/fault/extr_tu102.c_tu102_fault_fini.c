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
struct nvkm_fault {scalar_t__* buffer; TYPE_2__* func; int /*<<< orphan*/  nrpfb; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fini ) (scalar_t__) ;} ;
struct TYPE_4__ {TYPE_1__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_notify_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void
tu102_fault_fini(struct nvkm_fault *fault)
{
	nvkm_notify_put(&fault->nrpfb);
	if (fault->buffer[0])
		fault->func->buffer.fini(fault->buffer[0]);
	/*XXX: disable priv faults */
}