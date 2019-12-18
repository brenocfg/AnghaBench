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
struct spi_nor {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SR_BP0 ; 
 int SR_BP1 ; 
 int SR_BP2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int read_sr (struct spi_nor*) ; 
 int spi_nor_wait_till_ready (struct spi_nor*) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 
 int write_sr (struct spi_nor*,int) ; 

__attribute__((used)) static int spi_nor_clear_sr_bp(struct spi_nor *nor)
{
	int ret;
	u8 mask = SR_BP2 | SR_BP1 | SR_BP0;

	ret = read_sr(nor);
	if (ret < 0) {
		dev_err(nor->dev, "error while reading status register\n");
		return ret;
	}

	write_enable(nor);

	ret = write_sr(nor, ret & ~mask);
	if (ret) {
		dev_err(nor->dev, "write to status register failed\n");
		return ret;
	}

	ret = spi_nor_wait_till_ready(nor);
	if (ret)
		dev_err(nor->dev, "timeout while writing status register\n");
	return ret;
}