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
typedef  int u16 ;
struct panel_drv_data {TYPE_1__* spi_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int JBT_COMMAND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spi_write (TYPE_1__*,int*,int) ; 

__attribute__((used)) static int jbt_ret_write_0(struct panel_drv_data *ddata, u8 reg)
{
	int rc;
	u16 tx_buf = JBT_COMMAND | reg;

	rc = spi_write(ddata->spi_dev, (u8 *)&tx_buf,
			1*sizeof(u16));
	if (rc != 0)
		dev_err(&ddata->spi_dev->dev,
			"jbt_ret_write_0 spi_write ret %d\n", rc);

	return rc;
}