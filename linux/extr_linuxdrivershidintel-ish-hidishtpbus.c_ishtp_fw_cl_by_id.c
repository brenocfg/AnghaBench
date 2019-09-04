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
typedef  scalar_t__ uint8_t ;
struct ishtp_device {int fw_clients_num; int /*<<< orphan*/  fw_clients_lock; TYPE_1__* fw_clients; } ;
struct TYPE_2__ {scalar_t__ client_id; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ishtp_fw_cl_by_id(struct ishtp_device *dev, uint8_t client_id)
{
	int i, res = -ENOENT;
	unsigned long	flags;

	spin_lock_irqsave(&dev->fw_clients_lock, flags);
	for (i = 0; i < dev->fw_clients_num; i++) {
		if (dev->fw_clients[i].client_id == client_id) {
			res = i;
			break;
		}
	}
	spin_unlock_irqrestore(&dev->fw_clients_lock, flags);

	return res;
}