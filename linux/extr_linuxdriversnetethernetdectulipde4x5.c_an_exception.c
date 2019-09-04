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
typedef  int u_short ;
struct TYPE_2__ {scalar_t__ sub_system_id; scalar_t__ sub_vendor_id; } ;
struct de4x5_private {TYPE_1__ srom; } ;

/* Variables and functions */

__attribute__((used)) static int
an_exception(struct de4x5_private *lp)
{
    if ((*(u_short *)lp->srom.sub_vendor_id == 0x00c0) &&
	(*(u_short *)lp->srom.sub_system_id == 0x95e0)) {
	return -1;
    }

    return 0;
}