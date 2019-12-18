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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct ksz_device {int /*<<< orphan*/ * regmap; } ;

/* Variables and functions */
 int regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ swab32 (scalar_t__) ; 
 int /*<<< orphan*/  swab64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ksz_read64(struct ksz_device *dev, u32 reg, u64 *val)
{
	u32 value[2];
	int ret;

	ret = regmap_bulk_read(dev->regmap[2], reg, value, 2);
	if (!ret) {
		/* Ick! ToDo: Add 64bit R/W to regmap on 32bit systems */
		value[0] = swab32(value[0]);
		value[1] = swab32(value[1]);
		*val = swab64((u64)*value);
	}

	return ret;
}