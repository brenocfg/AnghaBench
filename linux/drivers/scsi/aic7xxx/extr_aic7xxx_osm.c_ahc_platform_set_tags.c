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
typedef  scalar_t__ u_int ;
struct scsi_device {int dummy; } ;
struct ahc_softc {int dummy; } ;
struct ahc_linux_device {int flags; int active; int openings; scalar_t__ maxtags; int /*<<< orphan*/  qfrozen; } ;
struct ahc_devinfo {int dummy; } ;
typedef  int ahc_queue_alg ;

/* Variables and functions */
 int AHC_DEV_FREEZE_TIL_EMPTY ; 
 int AHC_DEV_PERIODIC_OTAG ; 
#define  AHC_DEV_Q_BASIC 132 
#define  AHC_DEV_Q_TAGGED 131 
#define  AHC_QUEUE_BASIC 130 
#define  AHC_QUEUE_NONE 129 
#define  AHC_QUEUE_TAGGED 128 
 scalar_t__ ahc_linux_user_tagdepth (struct ahc_softc*,struct ahc_devinfo*) ; 
 scalar_t__ aic7xxx_periodic_otag ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int) ; 
 struct ahc_linux_device* scsi_transport_device_data (struct scsi_device*) ; 

void
ahc_platform_set_tags(struct ahc_softc *ahc, struct scsi_device *sdev,
		      struct ahc_devinfo *devinfo, ahc_queue_alg alg)
{
	struct ahc_linux_device *dev;
	int was_queuing;
	int now_queuing;

	if (sdev == NULL)
		return;
	dev = scsi_transport_device_data(sdev);

	was_queuing = dev->flags & (AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED);
	switch (alg) {
	default:
	case AHC_QUEUE_NONE:
		now_queuing = 0;
		break; 
	case AHC_QUEUE_BASIC:
		now_queuing = AHC_DEV_Q_BASIC;
		break;
	case AHC_QUEUE_TAGGED:
		now_queuing = AHC_DEV_Q_TAGGED;
		break;
	}
	if ((dev->flags & AHC_DEV_FREEZE_TIL_EMPTY) == 0
	 && (was_queuing != now_queuing)
	 && (dev->active != 0)) {
		dev->flags |= AHC_DEV_FREEZE_TIL_EMPTY;
		dev->qfrozen++;
	}

	dev->flags &= ~(AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED|AHC_DEV_PERIODIC_OTAG);
	if (now_queuing) {
		u_int usertags;

		usertags = ahc_linux_user_tagdepth(ahc, devinfo);
		if (!was_queuing) {
			/*
			 * Start out aggressively and allow our
			 * dynamic queue depth algorithm to take
			 * care of the rest.
			 */
			dev->maxtags = usertags;
			dev->openings = dev->maxtags - dev->active;
		}
		if (dev->maxtags == 0) {
			/*
			 * Queueing is disabled by the user.
			 */
			dev->openings = 1;
		} else if (alg == AHC_QUEUE_TAGGED) {
			dev->flags |= AHC_DEV_Q_TAGGED;
			if (aic7xxx_periodic_otag != 0)
				dev->flags |= AHC_DEV_PERIODIC_OTAG;
		} else
			dev->flags |= AHC_DEV_Q_BASIC;
	} else {
		/* We can only have one opening. */
		dev->maxtags = 0;
		dev->openings =  1 - dev->active;
	}
	switch ((dev->flags & (AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED))) {
	case AHC_DEV_Q_BASIC:
	case AHC_DEV_Q_TAGGED:
		scsi_change_queue_depth(sdev,
				dev->openings + dev->active);
		break;
	default:
		/*
		 * We allow the OS to queue 2 untagged transactions to
		 * us at any time even though we can only execute them
		 * serially on the controller/device.  This should
		 * remove some latency.
		 */
		scsi_change_queue_depth(sdev, 2);
		break;
	}
}