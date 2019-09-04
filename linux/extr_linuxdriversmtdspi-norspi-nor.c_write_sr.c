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
struct spi_nor {int (* write_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/ * cmd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPINOR_OP_WRSR ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int write_sr(struct spi_nor *nor, u8 val)
{
	nor->cmd_buf[0] = val;
	return nor->write_reg(nor, SPINOR_OP_WRSR, nor->cmd_buf, 1);
}