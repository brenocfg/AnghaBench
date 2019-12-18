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
struct vfio_ap_queue_reserved {unsigned long* apid; unsigned long* apqi; int reserved; } ;
struct device {int dummy; } ;
struct ap_queue {scalar_t__ qid; } ;
typedef  scalar_t__ ap_qid_t ;

/* Variables and functions */
 scalar_t__ AP_MKQID (unsigned long,unsigned long) ; 
 unsigned long AP_QID_CARD (scalar_t__) ; 
 unsigned long AP_QID_QUEUE (scalar_t__) ; 
 int EINVAL ; 
 struct ap_queue* to_ap_queue (struct device*) ; 

__attribute__((used)) static int vfio_ap_has_queue(struct device *dev, void *data)
{
	struct vfio_ap_queue_reserved *qres = data;
	struct ap_queue *ap_queue = to_ap_queue(dev);
	ap_qid_t qid;
	unsigned long id;

	if (qres->apid && qres->apqi) {
		qid = AP_MKQID(*qres->apid, *qres->apqi);
		if (qid == ap_queue->qid)
			qres->reserved = true;
	} else if (qres->apid && !qres->apqi) {
		id = AP_QID_CARD(ap_queue->qid);
		if (id == *qres->apid)
			qres->reserved = true;
	} else if (!qres->apid && qres->apqi) {
		id = AP_QID_QUEUE(ap_queue->qid);
		if (id == *qres->apqi)
			qres->reserved = true;
	} else {
		return -EINVAL;
	}

	return 0;
}