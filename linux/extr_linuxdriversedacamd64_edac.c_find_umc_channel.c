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
struct mce {int ipid; } ;
struct amd64_pvt {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_umc_channel(struct amd64_pvt *pvt, struct mce *m)
{
	u32 umc_instance_id[] = {0x50f00, 0x150f00};
	u32 instance_id = m->ipid & GENMASK(31, 0);
	int i, channel = -1;

	for (i = 0; i < ARRAY_SIZE(umc_instance_id); i++)
		if (umc_instance_id[i] == instance_id)
			channel = i;

	return channel;
}