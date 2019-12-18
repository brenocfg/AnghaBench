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
struct subchannel {int /*<<< orphan*/  dev; } ;
struct schib {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct subchannel*) ; 
 int PTR_ERR (struct subchannel*) ; 
 struct subchannel* css_alloc_subchannel (struct subchannel_id,struct schib*) ; 
 int css_register_subchannel (struct subchannel*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int css_probe_device(struct subchannel_id schid, struct schib *schib)
{
	struct subchannel *sch;
	int ret;

	sch = css_alloc_subchannel(schid, schib);
	if (IS_ERR(sch))
		return PTR_ERR(sch);

	ret = css_register_subchannel(sch);
	if (ret)
		put_device(&sch->dev);

	return ret;
}