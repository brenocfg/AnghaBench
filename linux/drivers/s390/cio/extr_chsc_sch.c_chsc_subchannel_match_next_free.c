#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ena; } ;
struct TYPE_4__ {int /*<<< orphan*/  scsw; TYPE_1__ pmcw; } ;
struct subchannel {TYPE_2__ schib; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsw_fctl (int /*<<< orphan*/ *) ; 
 struct subchannel* to_subchannel (struct device*) ; 

__attribute__((used)) static int chsc_subchannel_match_next_free(struct device *dev, const void *data)
{
	struct subchannel *sch = to_subchannel(dev);

	return sch->schib.pmcw.ena && !scsw_fctl(&sch->schib.scsw);
}