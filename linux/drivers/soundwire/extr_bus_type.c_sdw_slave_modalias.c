#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mfg_id; int part_id; } ;
struct sdw_slave {TYPE_1__ id; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,int,int) ; 

int sdw_slave_modalias(const struct sdw_slave *slave, char *buf, size_t size)
{
	/* modalias is sdw:m<mfg_id>p<part_id> */

	return snprintf(buf, size, "sdw:m%04Xp%04X\n",
			slave->id.mfg_id, slave->id.part_id);
}