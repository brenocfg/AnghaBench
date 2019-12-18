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
struct subchannel_id {int dummy; } ;
struct subchannel {int /*<<< orphan*/  schid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int schid_equal (int /*<<< orphan*/ *,struct subchannel_id*) ; 
 struct subchannel* to_subchannel (struct device*) ; 

__attribute__((used)) static int
check_subchannel(struct device *dev, const void *data)
{
	struct subchannel *sch;
	struct subchannel_id *schid = (void *)data;

	sch = to_subchannel(dev);
	return schid_equal(&sch->schid, schid);
}