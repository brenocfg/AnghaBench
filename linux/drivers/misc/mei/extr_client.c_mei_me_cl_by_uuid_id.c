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
typedef  int /*<<< orphan*/  uuid_le ;
typedef  int /*<<< orphan*/  u8 ;
struct mei_me_client {int dummy; } ;
struct mei_device {int /*<<< orphan*/  me_clients_rwsem; } ;

/* Variables and functions */
 struct mei_me_client* __mei_me_cl_by_uuid_id (struct mei_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct mei_me_client *mei_me_cl_by_uuid_id(struct mei_device *dev,
					   const uuid_le *uuid, u8 client_id)
{
	struct mei_me_client *me_cl;

	down_read(&dev->me_clients_rwsem);
	me_cl = __mei_me_cl_by_uuid_id(dev, uuid, client_id);
	up_read(&dev->me_clients_rwsem);

	return me_cl;
}