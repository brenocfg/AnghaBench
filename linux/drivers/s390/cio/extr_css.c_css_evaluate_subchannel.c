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

/* Variables and functions */
 int EAGAIN ; 
 int css_evaluate_known_subchannel (struct subchannel*,int) ; 
 int css_evaluate_new_subchannel (struct subchannel_id,int) ; 
 int /*<<< orphan*/  css_schedule_eval (struct subchannel_id) ; 
 struct subchannel* get_subchannel_by_schid (struct subchannel_id) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void css_evaluate_subchannel(struct subchannel_id schid, int slow)
{
	struct subchannel *sch;
	int ret;

	sch = get_subchannel_by_schid(schid);
	if (sch) {
		ret = css_evaluate_known_subchannel(sch, slow);
		put_device(&sch->dev);
	} else
		ret = css_evaluate_new_subchannel(schid, slow);
	if (ret == -EAGAIN)
		css_schedule_eval(schid);
}