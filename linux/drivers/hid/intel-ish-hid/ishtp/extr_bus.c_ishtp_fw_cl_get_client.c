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
struct TYPE_2__ {scalar_t__ fixed_address; } ;
struct ishtp_fw_client {TYPE_1__ props; } ;
struct ishtp_device {struct ishtp_fw_client* fw_clients; int /*<<< orphan*/  fw_clients_lock; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int ishtp_fw_cl_by_uuid (struct ishtp_device*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct ishtp_fw_client *ishtp_fw_cl_get_client(struct ishtp_device *dev,
					       const guid_t *uuid)
{
	int i;
	unsigned long flags;

	spin_lock_irqsave(&dev->fw_clients_lock, flags);
	i = ishtp_fw_cl_by_uuid(dev, uuid);
	spin_unlock_irqrestore(&dev->fw_clients_lock, flags);
	if (i < 0 || dev->fw_clients[i].props.fixed_address)
		return NULL;

	return &dev->fw_clients[i];
}