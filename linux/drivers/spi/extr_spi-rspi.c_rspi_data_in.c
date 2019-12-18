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
typedef  int u8 ;
struct rspi_data {TYPE_1__* ctlr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int rspi_read_data (struct rspi_data*) ; 
 int rspi_wait_for_rx_full (struct rspi_data*) ; 

__attribute__((used)) static int rspi_data_in(struct rspi_data *rspi)
{
	int error;
	u8 data;

	error = rspi_wait_for_rx_full(rspi);
	if (error < 0) {
		dev_err(&rspi->ctlr->dev, "receive timeout\n");
		return error;
	}
	data = rspi_read_data(rspi);
	return data;
}