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
struct spi_nor {int (* read_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SPINOR_OP_RDSR ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int read_sr(struct spi_nor *nor)
{
	int ret;
	u8 val;

	ret = nor->read_reg(nor, SPINOR_OP_RDSR, &val, 1);
	if (ret < 0) {
		pr_err("error %d reading SR\n", (int) ret);
		return ret;
	}

	return val;
}