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
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
struct uwb_ie_drp {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ uwb_dev_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool uwb_drp_involves_us(struct uwb_rc *rc, struct uwb_ie_drp *drp_ie)
{
	return uwb_dev_addr_cmp(&rc->uwb_dev.dev_addr, &drp_ie->dev_addr) == 0;
}