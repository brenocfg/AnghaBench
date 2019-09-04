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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bnx2x_null_format_ver (int,int /*<<< orphan*/ *,int*) ; 
 int scnprintf (int /*<<< orphan*/ *,int,char*,int,int,int) ; 

__attribute__((used)) static int bnx2x_3_seq_format_ver(u32 num, u8 *str, u16 *len)
{
	u16 ret;

	if (*len < 10) {
		/* Need more than 10chars for this format */
		bnx2x_null_format_ver(num, str, len);
		return -EINVAL;
	}

	ret = scnprintf(str, *len, "%hhx.%hhx.%hhx", num >> 16, num >> 8, num);
	*len -= ret;
	return 0;
}