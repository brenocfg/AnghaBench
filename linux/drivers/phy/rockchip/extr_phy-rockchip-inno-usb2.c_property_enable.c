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
struct usb2phy_reg {unsigned int enable; unsigned int disable; unsigned int bitstart; int /*<<< orphan*/  offset; int /*<<< orphan*/  bitend; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int BIT_WRITEABLE_SHIFT ; 
 unsigned int GENMASK (int /*<<< orphan*/ ,unsigned int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int property_enable(struct regmap *base,
				  const struct usb2phy_reg *reg, bool en)
{
	unsigned int val, mask, tmp;

	tmp = en ? reg->enable : reg->disable;
	mask = GENMASK(reg->bitend, reg->bitstart);
	val = (tmp << reg->bitstart) | (mask << BIT_WRITEABLE_SHIFT);

	return regmap_write(base, reg->offset, val);
}