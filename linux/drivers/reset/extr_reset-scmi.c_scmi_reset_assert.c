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
struct scmi_handle {TYPE_1__* reset_ops; } ;
struct reset_controller_dev {int dummy; } ;
struct TYPE_2__ {int (* assert ) (struct scmi_handle const*,unsigned long) ;} ;

/* Variables and functions */
 int stub1 (struct scmi_handle const*,unsigned long) ; 
 struct scmi_handle* to_scmi_handle (struct reset_controller_dev*) ; 

__attribute__((used)) static int
scmi_reset_assert(struct reset_controller_dev *rcdev, unsigned long id)
{
	const struct scmi_handle *handle = to_scmi_handle(rcdev);

	return handle->reset_ops->assert(handle, id);
}