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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int RC5T583_DS_DC0 ; 
 int /*<<< orphan*/  RICOH_ONOFFSEL_REG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int rc5t583_set_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __rc5t583_set_ext_pwrreq2_control(struct device *dev,
	int id, int ext_pwr)
{
	int ret;

	if (id != RC5T583_DS_DC0) {
		dev_err(dev, "PWRREQ2 is invalid control for rail %d\n", id);
		return -EINVAL;
	}

	ret = rc5t583_set_bits(dev, RICOH_ONOFFSEL_REG, BIT(2));
	if (ret < 0)
		dev_err(dev, "Error in updating the ONOFFSEL 0x10 register\n");
	return ret;
}