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
struct tc_cls_flower_offload {int command; int /*<<< orphan*/  cookie; } ;
struct qede_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSFLOWER_DESTROY 129 
#define  TC_CLSFLOWER_REPLACE 128 
 int qede_add_tc_flower_fltr (struct qede_dev*,int /*<<< orphan*/ ,struct tc_cls_flower_offload*) ; 
 int qede_delete_flow_filter (struct qede_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qede_set_flower(struct qede_dev *edev, struct tc_cls_flower_offload *f,
		__be16 proto)
{
	switch (f->command) {
	case TC_CLSFLOWER_REPLACE:
		return qede_add_tc_flower_fltr(edev, proto, f);
	case TC_CLSFLOWER_DESTROY:
		return qede_delete_flow_filter(edev, f->cookie);
	default:
		return -EOPNOTSUPP;
	}
}