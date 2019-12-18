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
struct cfspi_ifc {scalar_t__ priv; } ;
struct cfspi {int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfspi_xfer_done_cb(struct cfspi_ifc *ifc)
{
	struct cfspi *cfspi = (struct cfspi *)ifc->priv;

	/* Transfer done, complete work queue */
	complete(&cfspi->comp);
}