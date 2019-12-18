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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int w5100_spi_write (struct net_device*,scalar_t__,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int w5100_spi_writebulk(struct net_device *ndev, u32 addr, const u8 *buf,
			       int len)
{
	int i;

	for (i = 0; i < len; i++) {
		int ret = w5100_spi_write(ndev, addr + i, buf[i]);

		if (ret)
			return ret;
	}

	return 0;
}