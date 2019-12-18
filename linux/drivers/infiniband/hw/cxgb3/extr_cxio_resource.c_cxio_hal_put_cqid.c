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
typedef  int /*<<< orphan*/  u32 ;
struct cxio_hal_resource {int /*<<< orphan*/  cqid_fifo_lock; int /*<<< orphan*/  cqid_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxio_hal_put_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cxio_hal_put_cqid(struct cxio_hal_resource *rscp, u32 cqid)
{
	cxio_hal_put_resource(&rscp->cqid_fifo, &rscp->cqid_fifo_lock, cqid);
}