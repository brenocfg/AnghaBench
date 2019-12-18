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
struct qedi_ctx {int /*<<< orphan*/  cdev; } ;
struct qed_link_output {int speed; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_link ) (int /*<<< orphan*/ ,struct qed_link_output*) ;} ;

/* Variables and functions */
 struct qedi_ctx* qedi_dev_to_hba (struct device*) ; 
 TYPE_2__* qedi_ops ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_link_output*) ; 

__attribute__((used)) static ssize_t qedi_show_speed(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct qedi_ctx *qedi = qedi_dev_to_hba(dev);
	struct qed_link_output if_link;

	qedi_ops->common->get_link(qedi->cdev, &if_link);

	return sprintf(buf, "%d Gbit\n", if_link.speed / 1000);
}