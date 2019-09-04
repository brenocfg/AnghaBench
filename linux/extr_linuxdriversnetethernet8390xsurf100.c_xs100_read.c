#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct xsurf100_ax_plat_data {scalar_t__ data_area; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ei_device {scalar_t__ mem; } ;

/* Variables and functions */
 scalar_t__ NE_DATAPORT ; 
 unsigned int XS100_8390_DATA_AREA_SIZE ; 
 scalar_t__ XS100_8390_DATA_READ32_BASE ; 
 struct xsurf100_ax_plat_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ei_inb (scalar_t__) ; 
 int /*<<< orphan*/  ei_inw (scalar_t__) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z_memcpy_fromio32 (void*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void xs100_read(struct net_device *dev, void *dst, unsigned int count)
{
	struct ei_device *ei_local = netdev_priv(dev);
	struct platform_device *pdev = to_platform_device(dev->dev.parent);
	struct xsurf100_ax_plat_data *xs100 = dev_get_platdata(&pdev->dev);

	/* copy whole blocks */
	while (count > XS100_8390_DATA_AREA_SIZE) {
		z_memcpy_fromio32(dst, xs100->data_area +
				  XS100_8390_DATA_READ32_BASE,
				  XS100_8390_DATA_AREA_SIZE);
		dst += XS100_8390_DATA_AREA_SIZE;
		count -= XS100_8390_DATA_AREA_SIZE;
	}
	/* copy whole dwords */
	z_memcpy_fromio32(dst, xs100->data_area + XS100_8390_DATA_READ32_BASE,
			  count & ~3);
	dst += count & ~3;
	if (count & 2) {
		*(uint16_t *)dst = ei_inw(ei_local->mem + NE_DATAPORT);
		dst += 2;
	}
	if (count & 1)
		*(uint8_t *)dst = ei_inb(ei_local->mem + NE_DATAPORT);
}