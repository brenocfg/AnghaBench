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
 int EFAULT ; 
 int /*<<< orphan*/  gvt_err (char*,int,int) ; 

__attribute__((used)) static int gvt_check_valid_cmd_length(int len, int valid_len)
{
	if (valid_len != len) {
		gvt_err("len is not valid:  len=%u  valid_len=%u\n",
			len, valid_len);
		return -EFAULT;
	}
	return 0;
}