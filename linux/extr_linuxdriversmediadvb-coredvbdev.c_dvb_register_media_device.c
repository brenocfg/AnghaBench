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

__attribute__((used)) static int dvb_register_media_device(struct dvb_device *dvbdev,
				     int type, int minor,
				     unsigned demux_sink_pads)
{
#if defined(CONFIG_MEDIA_CONTROLLER_DVB)
	struct media_link *link;
	u32 intf_type;
	int ret;

	if (!dvbdev->adapter->mdev)
		return 0;

	ret = dvb_create_media_entity(dvbdev, type, demux_sink_pads);
	if (ret)
		return ret;

	switch (type) {
	case DVB_DEVICE_FRONTEND:
		intf_type = MEDIA_INTF_T_DVB_FE;
		break;
	case DVB_DEVICE_DEMUX:
		intf_type = MEDIA_INTF_T_DVB_DEMUX;
		break;
	case DVB_DEVICE_DVR:
		intf_type = MEDIA_INTF_T_DVB_DVR;
		break;
	case DVB_DEVICE_CA:
		intf_type = MEDIA_INTF_T_DVB_CA;
		break;
	case DVB_DEVICE_NET:
		intf_type = MEDIA_INTF_T_DVB_NET;
		break;
	default:
		return 0;
	}

	dvbdev->intf_devnode = media_devnode_create(dvbdev->adapter->mdev,
						    intf_type, 0,
						    DVB_MAJOR, minor);

	if (!dvbdev->intf_devnode)
		return -ENOMEM;

	/*
	 * Create the "obvious" link, e. g. the ones that represent
	 * a direct association between an interface and an entity.
	 * Other links should be created elsewhere, like:
	 *		DVB FE intf    -> tuner
	 *		DVB demux intf -> dvr
	 */

	if (!dvbdev->entity)
		return 0;

	link = media_create_intf_link(dvbdev->entity,
				      &dvbdev->intf_devnode->intf,
				      MEDIA_LNK_FL_ENABLED |
				      MEDIA_LNK_FL_IMMUTABLE);
	if (!link)
		return -ENOMEM;
#endif
	return 0;
}