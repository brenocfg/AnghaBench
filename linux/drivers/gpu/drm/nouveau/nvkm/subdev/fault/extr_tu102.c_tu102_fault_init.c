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
struct nvkm_fault {int /*<<< orphan*/  nrpfb; int /*<<< orphan*/ * buffer; TYPE_2__* func; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_notify_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tu102_fault_init(struct nvkm_fault *fault)
{
	/*XXX: enable priv faults */
	fault->func->buffer.init(fault->buffer[0]);
	nvkm_notify_get(&fault->nrpfb);
}