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
typedef  int /*<<< orphan*/  uuid_le ;
struct ishtp_device {int fw_clients_num; TYPE_2__* fw_clients; } ;
struct TYPE_3__ {int /*<<< orphan*/  protocol_name; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ uuid_le_cmp (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

int ishtp_fw_cl_by_uuid(struct ishtp_device *dev, const uuid_le *uuid)
{
	int i, res = -ENOENT;

	for (i = 0; i < dev->fw_clients_num; ++i) {
		if (uuid_le_cmp(*uuid, dev->fw_clients[i].props.protocol_name)
				== 0) {
			res = i;
			break;
		}
	}
	return res;
}