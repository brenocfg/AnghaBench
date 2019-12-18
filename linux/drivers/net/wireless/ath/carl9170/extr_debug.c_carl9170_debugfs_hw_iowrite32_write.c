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
typedef  int u32 ;
struct ar9170 {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int E2BIG ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int carl9170_write_reg (struct ar9170*,int,int) ; 
 int sscanf (char const*,char*,int*,int*) ; 

__attribute__((used)) static ssize_t carl9170_debugfs_hw_iowrite32_write(struct ar9170 *ar,
	const char *buf, size_t count)
{
	int err = 0, max_len = 22, res;
	u32 reg, val;

	if (!count)
		return 0;

	if (count > max_len)
		return -E2BIG;

	res = sscanf(buf, "0x%X 0x%X", &reg, &val);
	if (res != 2) {
		err = -EINVAL;
		goto out;
	}

	if (reg <= 0x100000 || reg >= 0x280000) {
		err = -EADDRNOTAVAIL;
		goto out;
	}

	if (reg & 3) {
		err = -EINVAL;
		goto out;
	}

	err = carl9170_write_reg(ar, reg, val);
	if (err)
		goto out;

out:
	return err ? err : count;
}