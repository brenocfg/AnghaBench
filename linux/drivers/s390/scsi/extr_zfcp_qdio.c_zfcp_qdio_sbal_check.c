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
struct zfcp_qdio {TYPE_1__* adapter; int /*<<< orphan*/  req_q_free; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ZFCP_STATUS_ADAPTER_QDIOUP ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zfcp_qdio_sbal_check(struct zfcp_qdio *qdio)
{
	if (atomic_read(&qdio->req_q_free) ||
	    !(atomic_read(&qdio->adapter->status) & ZFCP_STATUS_ADAPTER_QDIOUP))
		return 1;
	return 0;
}