#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int opmode; } ;
struct airo_info {int /*<<< orphan*/  flags; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  cfgr ;
typedef  TYPE_1__ ConfigRid ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ADHOC ; 
 int /*<<< orphan*/  FLAG_COMMIT ; 
 int /*<<< orphan*/  FLAG_RESET ; 
 int MODE_CFG_MASK ; 
 int MODE_STA_IBSS ; 
 int PC4500_writerid (struct airo_info*,int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  RID_CONFIG ; 
 int SUCCESS ; 
 int /*<<< orphan*/  checkThrottle (struct airo_info*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int writeConfigRid(struct airo_info *ai, int lock)
{
	ConfigRid cfgr;

	if (!test_bit (FLAG_COMMIT, &ai->flags))
		return SUCCESS;

	clear_bit (FLAG_COMMIT, &ai->flags);
	clear_bit (FLAG_RESET, &ai->flags);
	checkThrottle(ai);
	cfgr = ai->config;

	if ((cfgr.opmode & MODE_CFG_MASK) == MODE_STA_IBSS)
		set_bit(FLAG_ADHOC, &ai->flags);
	else
		clear_bit(FLAG_ADHOC, &ai->flags);

	return PC4500_writerid( ai, RID_CONFIG, &cfgr, sizeof(cfgr), lock);
}