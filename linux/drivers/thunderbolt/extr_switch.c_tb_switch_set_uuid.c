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
typedef  int /*<<< orphan*/  uuid ;
typedef  int u32 ;
struct tb_switch {int uid; int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmemdup (int*,int,int /*<<< orphan*/ ) ; 
 int tb_lc_read_uuid (struct tb_switch*,int*) ; 

__attribute__((used)) static int tb_switch_set_uuid(struct tb_switch *sw)
{
	u32 uuid[4];
	int ret;

	if (sw->uuid)
		return 0;

	/*
	 * The newer controllers include fused UUID as part of link
	 * controller specific registers
	 */
	ret = tb_lc_read_uuid(sw, uuid);
	if (ret) {
		/*
		 * ICM generates UUID based on UID and fills the upper
		 * two words with ones. This is not strictly following
		 * UUID format but we want to be compatible with it so
		 * we do the same here.
		 */
		uuid[0] = sw->uid & 0xffffffff;
		uuid[1] = (sw->uid >> 32) & 0xffffffff;
		uuid[2] = 0xffffffff;
		uuid[3] = 0xffffffff;
	}

	sw->uuid = kmemdup(uuid, sizeof(uuid), GFP_KERNEL);
	if (!sw->uuid)
		return -ENOMEM;
	return 0;
}