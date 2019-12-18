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
struct spi_nor {int flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int SNOR_F_USE_CLSR ; 
 int SR_E_ERR ; 
 int SR_P_ERR ; 
 int SR_WIP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int read_sr (struct spi_nor*) ; 
 int /*<<< orphan*/  spi_nor_clear_sr (struct spi_nor*) ; 

__attribute__((used)) static int spi_nor_sr_ready(struct spi_nor *nor)
{
	int sr = read_sr(nor);
	if (sr < 0)
		return sr;

	if (nor->flags & SNOR_F_USE_CLSR && sr & (SR_E_ERR | SR_P_ERR)) {
		if (sr & SR_E_ERR)
			dev_err(nor->dev, "Erase Error occurred\n");
		else
			dev_err(nor->dev, "Programming Error occurred\n");

		spi_nor_clear_sr(nor);
		return -EIO;
	}

	return !(sr & SR_WIP);
}