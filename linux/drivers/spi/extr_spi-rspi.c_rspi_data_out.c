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
typedef  int /*<<< orphan*/  u8 ;
struct rspi_data {TYPE_1__* ctlr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int rspi_wait_for_tx_empty (struct rspi_data*) ; 
 int /*<<< orphan*/  rspi_write_data (struct rspi_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rspi_data_out(struct rspi_data *rspi, u8 data)
{
	int error = rspi_wait_for_tx_empty(rspi);
	if (error < 0) {
		dev_err(&rspi->ctlr->dev, "transmit timeout\n");
		return error;
	}
	rspi_write_data(rspi, data);
	return 0;
}