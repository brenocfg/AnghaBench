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
struct spi_nor {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int SR_QUAD_EN_MX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int read_sr (struct spi_nor*) ; 
 int spi_nor_wait_till_ready (struct spi_nor*) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 
 int /*<<< orphan*/  write_sr (struct spi_nor*,int) ; 

__attribute__((used)) static int macronix_quad_enable(struct spi_nor *nor)
{
	int ret, val;

	val = read_sr(nor);
	if (val < 0)
		return val;
	if (val & SR_QUAD_EN_MX)
		return 0;

	write_enable(nor);

	write_sr(nor, val | SR_QUAD_EN_MX);

	ret = spi_nor_wait_till_ready(nor);
	if (ret)
		return ret;

	ret = read_sr(nor);
	if (!(ret > 0 && (ret & SR_QUAD_EN_MX))) {
		dev_err(nor->dev, "Macronix Quad bit not set\n");
		return -EINVAL;
	}

	return 0;
}