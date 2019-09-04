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
struct mei_fw_status {int dummy; } ;
struct mei_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* fw_status ) (struct mei_device*,struct mei_fw_status*) ;} ;

/* Variables and functions */
 int stub1 (struct mei_device*,struct mei_fw_status*) ; 

__attribute__((used)) static inline int mei_fw_status(struct mei_device *dev,
				struct mei_fw_status *fw_status)
{
	return dev->ops->fw_status(dev, fw_status);
}