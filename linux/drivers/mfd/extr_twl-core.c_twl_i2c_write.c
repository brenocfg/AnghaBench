#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct regmap {int dummy; } ;
struct TYPE_4__ {TYPE_1__* twl_map; } ;
struct TYPE_3__ {size_t base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EPERM ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,size_t,size_t,unsigned int) ; 
 int regmap_bulk_write (struct regmap*,size_t,size_t*,unsigned int) ; 
 struct regmap* twl_get_regmap (size_t) ; 
 TYPE_2__* twl_priv ; 

int twl_i2c_write(u8 mod_no, u8 *value, u8 reg, unsigned num_bytes)
{
	struct regmap *regmap = twl_get_regmap(mod_no);
	int ret;

	if (!regmap)
		return -EPERM;

	ret = regmap_bulk_write(regmap, twl_priv->twl_map[mod_no].base + reg,
				value, num_bytes);

	if (ret)
		pr_err("%s: Write failed (mod %d, reg 0x%02x count %d)\n",
		       DRIVER_NAME, mod_no, reg, num_bytes);

	return ret;
}