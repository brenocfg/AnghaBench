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
struct ar9170 {int erp_mode; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int CARL9170_ERP_INVALID ; 
 size_t EINVAL ; 
 int __CARL9170_ERP_NUM ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t carl9170_debugfs_erp_write(struct ar9170 *ar, const char *buf,
					  size_t count)
{
	int res, val;

	if (count < 1)
		return -EINVAL;

	res = sscanf(buf, "%d", &val);
	if (res != 1)
		return -EINVAL;

	if (!((val > CARL9170_ERP_INVALID) &&
	      (val < __CARL9170_ERP_NUM)))
		return -EINVAL;

	ar->erp_mode = val;
	return count;
}