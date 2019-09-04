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
struct spi_nor {int /*<<< orphan*/  (* read_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SPINOR_OP_RDID ; 
 int SPI_NOR_MAX_ID_LEN ; 
 int /*<<< orphan*/  stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void nxp_spifi_dummy_id_read(struct spi_nor *nor)
{
	u8 id[SPI_NOR_MAX_ID_LEN];
	nor->read_reg(nor, SPINOR_OP_RDID, id, SPI_NOR_MAX_ID_LEN);
}