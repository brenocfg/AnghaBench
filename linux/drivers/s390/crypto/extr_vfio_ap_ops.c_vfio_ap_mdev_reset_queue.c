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
struct ap_queue_status {int response_code; int /*<<< orphan*/  queue_empty; } ;

/* Variables and functions */
 int AP_MKQID (unsigned int,unsigned int) ; 
#define  AP_RESPONSE_BUSY 130 
#define  AP_RESPONSE_NORMAL 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct ap_queue_status ap_tapq (int,int /*<<< orphan*/ *) ; 
 struct ap_queue_status ap_zapq (int) ; 
 int /*<<< orphan*/  msleep (int) ; 

int vfio_ap_mdev_reset_queue(unsigned int apid, unsigned int apqi,
			     unsigned int retry)
{
	struct ap_queue_status status;
	int retry2 = 2;
	int apqn = AP_MKQID(apid, apqi);

	do {
		status = ap_zapq(apqn);
		switch (status.response_code) {
		case AP_RESPONSE_NORMAL:
			while (!status.queue_empty && retry2--) {
				msleep(20);
				status = ap_tapq(apqn, NULL);
			}
			WARN_ON_ONCE(retry2 <= 0);
			return 0;
		case AP_RESPONSE_RESET_IN_PROGRESS:
		case AP_RESPONSE_BUSY:
			msleep(20);
			break;
		default:
			/* things are really broken, give up */
			return -EIO;
		}
	} while (retry--);

	return -EBUSY;
}