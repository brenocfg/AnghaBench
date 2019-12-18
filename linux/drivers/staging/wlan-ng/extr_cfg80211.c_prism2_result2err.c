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

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
#define  P80211ENUM_resultcode_implementation_failure 130 
#define  P80211ENUM_resultcode_invalid_parameters 129 
#define  P80211ENUM_resultcode_not_supported 128 

__attribute__((used)) static int prism2_result2err(int prism2_result)
{
	int err = 0;

	switch (prism2_result) {
	case P80211ENUM_resultcode_invalid_parameters:
		err = -EINVAL;
		break;
	case P80211ENUM_resultcode_implementation_failure:
		err = -EIO;
		break;
	case P80211ENUM_resultcode_not_supported:
		err = -EOPNOTSUPP;
		break;
	default:
		err = 0;
		break;
	}

	return err;
}