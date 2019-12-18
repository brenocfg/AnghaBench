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
struct spi_nor {int* bouncebuf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CR_QUAD_EN_SPAN ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int read_sr (struct spi_nor*) ; 
 int write_sr_cr (struct spi_nor*,int*) ; 

__attribute__((used)) static int spansion_no_read_cr_quad_enable(struct spi_nor *nor)
{
	u8 *sr_cr = nor->bouncebuf;
	int ret;

	/* Keep the current value of the Status Register. */
	ret = read_sr(nor);
	if (ret < 0) {
		dev_err(nor->dev, "error while reading status register\n");
		return -EINVAL;
	}
	sr_cr[0] = ret;
	sr_cr[1] = CR_QUAD_EN_SPAN;

	return write_sr_cr(nor, sr_cr);
}