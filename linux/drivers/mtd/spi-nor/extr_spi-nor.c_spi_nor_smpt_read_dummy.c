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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct spi_nor {scalar_t__ read_dummy; } ;

/* Variables and functions */
 scalar_t__ SMPT_CMD_READ_DUMMY (int /*<<< orphan*/  const) ; 
 scalar_t__ SMPT_CMD_READ_DUMMY_IS_VARIABLE ; 

__attribute__((used)) static u8 spi_nor_smpt_read_dummy(const struct spi_nor *nor, const u32 settings)
{
	u8 read_dummy = SMPT_CMD_READ_DUMMY(settings);

	if (read_dummy == SMPT_CMD_READ_DUMMY_IS_VARIABLE)
		return nor->read_dummy;
	return read_dummy;
}