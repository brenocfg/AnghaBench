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
struct rcb_common_cb {int /*<<< orphan*/  dsaf_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_DSAF_IS_DEBUG (int /*<<< orphan*/ ) ; 
 int HNS_RCB_DEBUG_NW_ENGINE_NUM ; 
 int HNS_RCB_SERVICE_NW_ENGINE_NUM ; 

__attribute__((used)) static int hns_rcb_common_get_port_num(struct rcb_common_cb *rcb_common)
{
	if (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev))
		return HNS_RCB_SERVICE_NW_ENGINE_NUM;
	else
		return HNS_RCB_DEBUG_NW_ENGINE_NUM;
}