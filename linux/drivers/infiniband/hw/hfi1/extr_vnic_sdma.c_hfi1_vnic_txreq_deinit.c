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
struct TYPE_2__ {int /*<<< orphan*/ * txreq_cache; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

void hfi1_vnic_txreq_deinit(struct hfi1_devdata *dd)
{
	kmem_cache_destroy(dd->vnic.txreq_cache);
	dd->vnic.txreq_cache = NULL;
}