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
struct spi_controller {int dummy; } ;
struct mtk_spi_slave {int slave_aborted; int /*<<< orphan*/  xfer_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct mtk_spi_slave* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int mtk_slave_abort(struct spi_controller *ctlr)
{
	struct mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);

	mdata->slave_aborted = true;
	complete(&mdata->xfer_done);

	return 0;
}