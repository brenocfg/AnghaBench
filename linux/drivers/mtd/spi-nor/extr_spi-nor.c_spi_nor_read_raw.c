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
typedef  int u32 ;
struct spi_nor {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int spi_nor_read_data (struct spi_nor*,int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spi_nor_read_raw(struct spi_nor *nor, u32 addr, size_t len, u8 *buf)
{
	int ret;

	while (len) {
		ret = spi_nor_read_data(nor, addr, len, buf);
		if (ret < 0)
			return ret;
		if (!ret || ret > len)
			return -EIO;

		buf += ret;
		addr += ret;
		len -= ret;
	}
	return 0;
}