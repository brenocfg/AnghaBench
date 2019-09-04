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
typedef  int /*<<< orphan*/  u8 ;
struct rmi_spi_xport {int /*<<< orphan*/  page; } ;
struct rmi_spi_cmd {int /*<<< orphan*/  addr; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMI_PAGE_SELECT_REGISTER ; 
 int /*<<< orphan*/  RMI_SPI_WRITE ; 
 int rmi_spi_xfer (struct rmi_spi_xport*,struct rmi_spi_cmd*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rmi_set_page(struct rmi_spi_xport *rmi_spi, u8 page)
{
	struct rmi_spi_cmd cmd;
	int ret;

	cmd.op = RMI_SPI_WRITE;
	cmd.addr = RMI_PAGE_SELECT_REGISTER;

	ret = rmi_spi_xfer(rmi_spi, &cmd, &page, 1, NULL, 0);

	if (ret)
		rmi_spi->page = page;

	return ret;
}