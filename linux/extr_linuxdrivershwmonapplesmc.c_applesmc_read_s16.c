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
typedef  int s16 ;

/* Variables and functions */
 int applesmc_read_key (char const*,int*,int) ; 

__attribute__((used)) static int applesmc_read_s16(const char *key, s16 *value)
{
	u8 buffer[2];
	int ret;

	ret = applesmc_read_key(key, buffer, 2);
	if (ret)
		return ret;

	*value = ((s16)buffer[0] << 8) | buffer[1];
	return 0;
}