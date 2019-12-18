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
struct spi_nor {int /*<<< orphan*/  (* write ) (struct spi_nor*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*) ;scalar_t__ spimem; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  spi_nor_spimem_write_data (struct spi_nor*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (struct spi_nor*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static ssize_t spi_nor_write_data(struct spi_nor *nor, loff_t to, size_t len,
				  const u8 *buf)
{
	if (nor->spimem)
		return spi_nor_spimem_write_data(nor, to, len, buf);

	return nor->write(nor, to, len, buf);
}