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
struct nvm_geo {int all_luns; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 

__attribute__((used)) static int nvm_config_check_luns(struct nvm_geo *geo, int lun_begin,
				 int lun_end)
{
	if (lun_begin > lun_end || lun_end >= geo->all_luns) {
		pr_err("lun out of bound (%u:%u > %u)\n",
			lun_begin, lun_end, geo->all_luns - 1);
		return -EINVAL;
	}

	return 0;
}