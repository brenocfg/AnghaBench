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
typedef  enum ipl_type { ____Placeholder_ipl_type } ipl_type ;

/* Variables and functions */
 int EINVAL ; 
#define  IPL_TYPE_CCW 130 
#define  IPL_TYPE_FCP 129 
#define  IPL_TYPE_NSS 128 
 int /*<<< orphan*/  reipl_block_actual ; 
 int /*<<< orphan*/  reipl_block_ccw ; 
 int /*<<< orphan*/  reipl_block_fcp ; 
 int /*<<< orphan*/  reipl_block_nss ; 
 int reipl_capabilities ; 
 int reipl_type ; 

__attribute__((used)) static int reipl_set_type(enum ipl_type type)
{
	if (!(reipl_capabilities & type))
		return -EINVAL;

	switch(type) {
	case IPL_TYPE_CCW:
		reipl_block_actual = reipl_block_ccw;
		break;
	case IPL_TYPE_FCP:
		reipl_block_actual = reipl_block_fcp;
		break;
	case IPL_TYPE_NSS:
		reipl_block_actual = reipl_block_nss;
		break;
	default:
		break;
	}
	reipl_type = type;
	return 0;
}