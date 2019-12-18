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
struct device {int dummy; } ;

/* Variables and functions */
 struct iscsi_cls_session* iscsi_dev_to_session (struct device*) ; 
 int /*<<< orphan*/  iscsi_is_session_dev (struct device*) ; 

__attribute__((used)) static int iscsi_iter_session_fn(struct device *dev, void *data)
{
	void (* fn) (struct iscsi_cls_session *) = data;

	if (!iscsi_is_session_dev(dev))
		return 0;
	fn(iscsi_dev_to_session(dev));
	return 0;
}