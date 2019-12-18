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
typedef  int /*<<< orphan*/  u32 ;
struct sdw_slave {int dummy; } ;

/* Variables and functions */
 int sdw_nread (struct sdw_slave*,int /*<<< orphan*/ ,int,int*) ; 

int sdw_read(struct sdw_slave *slave, u32 addr)
{
	u8 buf;
	int ret;

	ret = sdw_nread(slave, addr, 1, &buf);
	if (ret < 0)
		return ret;
	else
		return buf;
}