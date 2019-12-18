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
struct dvb_device {size_t minor; int /*<<< orphan*/  list_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_class ; 
 int /*<<< orphan*/  dvb_media_device_free (struct dvb_device*) ; 
 int /*<<< orphan*/ ** dvb_minors ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minor_rwsem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void dvb_remove_device(struct dvb_device *dvbdev)
{
	if (!dvbdev)
		return;

	down_write(&minor_rwsem);
	dvb_minors[dvbdev->minor] = NULL;
	up_write(&minor_rwsem);

	dvb_media_device_free(dvbdev);

	device_destroy(dvb_class, MKDEV(DVB_MAJOR, dvbdev->minor));

	list_del (&dvbdev->list_head);
}