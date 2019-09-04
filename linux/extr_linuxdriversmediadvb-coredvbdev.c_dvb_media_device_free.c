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
struct dvb_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void dvb_media_device_free(struct dvb_device *dvbdev)
{
#if defined(CONFIG_MEDIA_CONTROLLER_DVB)
	if (dvbdev->entity) {
		media_device_unregister_entity(dvbdev->entity);
		kfree(dvbdev->entity);
		kfree(dvbdev->pads);
		dvbdev->entity = NULL;
		dvbdev->pads = NULL;
	}

	if (dvbdev->tsout_entity) {
		int i;

		for (i = 0; i < dvbdev->tsout_num_entities; i++) {
			media_device_unregister_entity(&dvbdev->tsout_entity[i]);
			kfree(dvbdev->tsout_entity[i].name);
		}
		kfree(dvbdev->tsout_entity);
		kfree(dvbdev->tsout_pads);
		dvbdev->tsout_entity = NULL;
		dvbdev->tsout_pads = NULL;

		dvbdev->tsout_num_entities = 0;
	}

	if (dvbdev->intf_devnode) {
		media_devnode_remove(dvbdev->intf_devnode);
		dvbdev->intf_devnode = NULL;
	}

	if (dvbdev->adapter->conn) {
		media_device_unregister_entity(dvbdev->adapter->conn);
		dvbdev->adapter->conn = NULL;
		kfree(dvbdev->adapter->conn_pads);
		dvbdev->adapter->conn_pads = NULL;
	}
#endif
}