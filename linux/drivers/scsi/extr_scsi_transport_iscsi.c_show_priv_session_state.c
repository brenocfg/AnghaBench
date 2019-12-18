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
struct iscsi_cls_session {int /*<<< orphan*/  state; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct iscsi_cls_session* iscsi_dev_to_session (int /*<<< orphan*/ ) ; 
 char* iscsi_session_state_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t
show_priv_session_state(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct iscsi_cls_session *session = iscsi_dev_to_session(dev->parent);
	return sprintf(buf, "%s\n", iscsi_session_state_name(session->state));
}