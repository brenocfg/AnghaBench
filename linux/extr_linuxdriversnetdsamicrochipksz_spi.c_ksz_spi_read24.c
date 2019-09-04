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
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int be32_to_cpu (int) ; 
 int ksz_spi_read (struct ksz_device*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ksz_spi_read24(struct ksz_device *dev, u32 reg, u32 *val)
{
	int ret;

	*val = 0;
	ret = ksz_spi_read(dev, reg, (u8 *)val, 3);
	if (!ret) {
		*val = be32_to_cpu(*val);
		/* convert to 24bit */
		*val >>= 8;
	}

	return ret;
}