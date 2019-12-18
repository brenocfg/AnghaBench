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
struct regulator_dev {int dummy; } ;
struct lp8788_buck {int /*<<< orphan*/  lp; } ;
typedef  enum lp8788_buck_id { ____Placeholder_lp8788_buck_id } lp8788_buck_id ;

/* Variables and functions */
 int EINVAL ; 
 int LP8788_VOUT_M ; 
 int /*<<< orphan*/  lp8788_is_valid_buck_addr (int) ; 
 int lp8788_read_byte (int /*<<< orphan*/ ,int,int*) ; 
 int lp8788_select_buck_vout_addr (struct lp8788_buck*,int) ; 
 struct lp8788_buck* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp8788_buck12_get_voltage_sel(struct regulator_dev *rdev)
{
	struct lp8788_buck *buck = rdev_get_drvdata(rdev);
	enum lp8788_buck_id id = rdev_get_id(rdev);
	int ret;
	u8 val, addr;

	addr = lp8788_select_buck_vout_addr(buck, id);
	if (!lp8788_is_valid_buck_addr(addr))
		return -EINVAL;

	ret = lp8788_read_byte(buck->lp, addr, &val);
	if (ret)
		return ret;

	return val & LP8788_VOUT_M;
}