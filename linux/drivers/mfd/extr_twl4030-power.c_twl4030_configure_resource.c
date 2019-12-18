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
typedef  int u8 ;
struct twl4030_resconfig {size_t resource; int devgroup; int type; int type2; int remap_off; int remap_sleep; } ;

/* Variables and functions */
 int DEV_GRP_MASK ; 
 scalar_t__ DEV_GRP_OFFSET ; 
 int DEV_GRP_SHIFT ; 
 int EINVAL ; 
 int OFF_STATE_MASK ; 
 int OFF_STATE_SHIFT ; 
 scalar_t__ REMAP_OFFSET ; 
 int SLEEP_STATE_MASK ; 
 int SLEEP_STATE_SHIFT ; 
 size_t TOTAL_RESOURCES ; 
 int TWL4030_RESCONFIG_UNDEF ; 
 int /*<<< orphan*/  TWL_MODULE_PM_RECEIVER ; 
 int TYPE2_MASK ; 
 int TYPE2_SHIFT ; 
 int TYPE_MASK ; 
 scalar_t__ TYPE_OFFSET ; 
 int TYPE_SHIFT ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int* res_config_addrs ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int twl4030_configure_resource(struct twl4030_resconfig *rconfig)
{
	int rconfig_addr;
	int err;
	u8 type;
	u8 grp;
	u8 remap;

	if (rconfig->resource > TOTAL_RESOURCES) {
		pr_err("TWL4030 Resource %d does not exist\n",
			rconfig->resource);
		return -EINVAL;
	}

	rconfig_addr = res_config_addrs[rconfig->resource];

	/* Set resource group */
	err = twl_i2c_read_u8(TWL_MODULE_PM_RECEIVER, &grp,
			      rconfig_addr + DEV_GRP_OFFSET);
	if (err) {
		pr_err("TWL4030 Resource %d group could not be read\n",
			rconfig->resource);
		return err;
	}

	if (rconfig->devgroup != TWL4030_RESCONFIG_UNDEF) {
		grp &= ~DEV_GRP_MASK;
		grp |= rconfig->devgroup << DEV_GRP_SHIFT;
		err = twl_i2c_write_u8(TWL_MODULE_PM_RECEIVER,
				       grp, rconfig_addr + DEV_GRP_OFFSET);
		if (err < 0) {
			pr_err("TWL4030 failed to program devgroup\n");
			return err;
		}
	}

	/* Set resource types */
	err = twl_i2c_read_u8(TWL_MODULE_PM_RECEIVER, &type,
				rconfig_addr + TYPE_OFFSET);
	if (err < 0) {
		pr_err("TWL4030 Resource %d type could not be read\n",
			rconfig->resource);
		return err;
	}

	if (rconfig->type != TWL4030_RESCONFIG_UNDEF) {
		type &= ~TYPE_MASK;
		type |= rconfig->type << TYPE_SHIFT;
	}

	if (rconfig->type2 != TWL4030_RESCONFIG_UNDEF) {
		type &= ~TYPE2_MASK;
		type |= rconfig->type2 << TYPE2_SHIFT;
	}

	err = twl_i2c_write_u8(TWL_MODULE_PM_RECEIVER,
				type, rconfig_addr + TYPE_OFFSET);
	if (err < 0) {
		pr_err("TWL4030 failed to program resource type\n");
		return err;
	}

	/* Set remap states */
	err = twl_i2c_read_u8(TWL_MODULE_PM_RECEIVER, &remap,
			      rconfig_addr + REMAP_OFFSET);
	if (err < 0) {
		pr_err("TWL4030 Resource %d remap could not be read\n",
			rconfig->resource);
		return err;
	}

	if (rconfig->remap_off != TWL4030_RESCONFIG_UNDEF) {
		remap &= ~OFF_STATE_MASK;
		remap |= rconfig->remap_off << OFF_STATE_SHIFT;
	}

	if (rconfig->remap_sleep != TWL4030_RESCONFIG_UNDEF) {
		remap &= ~SLEEP_STATE_MASK;
		remap |= rconfig->remap_sleep << SLEEP_STATE_SHIFT;
	}

	err = twl_i2c_write_u8(TWL_MODULE_PM_RECEIVER,
			       remap,
			       rconfig_addr + REMAP_OFFSET);
	if (err < 0) {
		pr_err("TWL4030 failed to program remap\n");
		return err;
	}

	return 0;
}