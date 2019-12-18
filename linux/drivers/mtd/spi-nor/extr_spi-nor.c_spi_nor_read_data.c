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
struct spi_nor {int /*<<< orphan*/  (* read ) (struct spi_nor*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ;scalar_t__ spimem; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  spi_nor_spimem_read_data (struct spi_nor*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct spi_nor*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t spi_nor_read_data(struct spi_nor *nor, loff_t from, size_t len,
				 u8 *buf)
{
	if (nor->spimem)
		return spi_nor_spimem_read_data(nor, from, len, buf);

	return nor->read(nor, from, len, buf);
}