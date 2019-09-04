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
struct elan_tp_data {TYPE_2__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  elan_sysfs_groups ; 
 int /*<<< orphan*/  sysfs_remove_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elan_remove_sysfs_groups(void *_data)
{
	struct elan_tp_data *data = _data;

	sysfs_remove_groups(&data->client->dev.kobj, elan_sysfs_groups);
}