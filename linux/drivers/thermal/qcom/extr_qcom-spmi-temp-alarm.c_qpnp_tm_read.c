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
typedef  unsigned int u8 ;
typedef  scalar_t__ u16 ;
struct qpnp_tm_chip {scalar_t__ base; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static int qpnp_tm_read(struct qpnp_tm_chip *chip, u16 addr, u8 *data)
{
	unsigned int val;
	int ret;

	ret = regmap_read(chip->map, chip->base + addr, &val);
	if (ret < 0)
		return ret;

	*data = val;
	return 0;
}