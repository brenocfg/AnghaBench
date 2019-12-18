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
struct ieee1394_device_id {int dummy; } ;
struct fw_unit {int dummy; } ;
struct fw_serial {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 TYPE_1__* fw_parent_device (struct fw_unit*) ; 
 int fwserial_add_peer (struct fw_serial*,struct fw_unit*) ; 
 int fwserial_create (struct fw_unit*) ; 
 int /*<<< orphan*/  fwserial_list_mutex ; 
 struct fw_serial* fwserial_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwserial_probe(struct fw_unit *unit,
			  const struct ieee1394_device_id *id)
{
	struct fw_serial *serial;
	int err;

	mutex_lock(&fwserial_list_mutex);
	serial = fwserial_lookup(fw_parent_device(unit)->card);
	if (!serial)
		err = fwserial_create(unit);
	else
		err = fwserial_add_peer(serial, unit);
	mutex_unlock(&fwserial_list_mutex);
	return err;
}