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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int ksz_spi_read (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ksz_spi_read16(struct ksz_device *dev, u32 reg, u16 *val)
{
	int ret = ksz_spi_read(dev, reg, (u8 *)val, 2);

	if (!ret)
		*val = be16_to_cpu(*val);

	return ret;
}