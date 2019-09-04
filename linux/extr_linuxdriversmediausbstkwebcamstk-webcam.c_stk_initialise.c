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
struct stk_camera {int dummy; } ;
struct regval {int reg; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ is_initialised (struct stk_camera*) ; 
 int /*<<< orphan*/  is_present (struct stk_camera*) ; 
 int /*<<< orphan*/  set_initialised (struct stk_camera*) ; 
 struct regval* stk1125_initvals ; 
 int stk_camera_write_reg (struct stk_camera*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stk_sensor_init (struct stk_camera*) ; 

__attribute__((used)) static int stk_initialise(struct stk_camera *dev)
{
	struct regval *rv;
	int ret;
	if (!is_present(dev))
		return -ENODEV;
	if (is_initialised(dev))
		return 0;
	rv = stk1125_initvals;
	while (rv->reg != 0xffff) {
		ret = stk_camera_write_reg(dev, rv->reg, rv->val);
		if (ret)
			return ret;
		rv++;
	}
	if (stk_sensor_init(dev) == 0) {
		set_initialised(dev);
		return 0;
	} else
		return -1;
}