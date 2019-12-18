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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * membase; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LTQ_PADC_AVAIL ; 
 int PORTS ; 
 TYPE_1__ falcon_info ; 
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad_r32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pinctrl_falcon_get_range_size(int id)
{
	u32 avail;

	if ((id >= PORTS) || (!falcon_info.membase[id]))
		return -EINVAL;

	avail = pad_r32(falcon_info.membase[id], LTQ_PADC_AVAIL);

	return fls(avail);
}