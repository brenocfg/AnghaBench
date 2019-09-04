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
typedef  int u8 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int cxd2880_write_spi (struct spi_device*,int*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cxd2880_spi_clear_ts_buffer(struct spi_device *spi)
{
	u8 data = 0x03;
	int ret;

	ret = cxd2880_write_spi(spi, &data, 1);

	if (ret)
		pr_err("write spi failed\n");

	return ret;
}