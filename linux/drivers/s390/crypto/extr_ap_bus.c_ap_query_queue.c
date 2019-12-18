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
struct ap_queue_status {int response_code; } ;
typedef  int /*<<< orphan*/  ap_qid_t ;

/* Variables and functions */
#define  AP_DEVICE_TYPE_CEX2A 139 
#define  AP_DEVICE_TYPE_CEX2C 138 
#define  AP_DEVICE_TYPE_CEX3A 137 
#define  AP_DEVICE_TYPE_CEX3C 136 
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
#define  AP_RESPONSE_BUSY 135 
#define  AP_RESPONSE_CHECKSTOPPED 134 
#define  AP_RESPONSE_DECONFIGURED 133 
#define  AP_RESPONSE_INVALID_ADDRESS 132 
#define  AP_RESPONSE_NORMAL 131 
#define  AP_RESPONSE_OTHERWISE_CHANGED 130 
#define  AP_RESPONSE_Q_NOT_AVAIL 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int /*<<< orphan*/  BUG () ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  ap_apft_available () ; 
 int ap_max_domain_id ; 
 int /*<<< orphan*/  ap_test_config_card_id (int /*<<< orphan*/ ) ; 
 struct ap_queue_status ap_test_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int ap_query_queue(ap_qid_t qid, int *queue_depth, int *device_type,
			  unsigned int *facilities)
{
	struct ap_queue_status status;
	unsigned long info;
	int nd;

	if (!ap_test_config_card_id(AP_QID_CARD(qid)))
		return -ENODEV;

	status = ap_test_queue(qid, ap_apft_available(), &info);
	switch (status.response_code) {
	case AP_RESPONSE_NORMAL:
		*queue_depth = (int)(info & 0xff);
		*device_type = (int)((info >> 24) & 0xff);
		*facilities = (unsigned int)(info >> 32);
		/* Update maximum domain id */
		nd = (info >> 16) & 0xff;
		/* if N bit is available, z13 and newer */
		if ((info & (1UL << 57)) && nd > 0)
			ap_max_domain_id = nd;
		else /* older machine types */
			ap_max_domain_id = 15;
		switch (*device_type) {
			/* For CEX2 and CEX3 the available functions
			 * are not reflected by the facilities bits.
			 * Instead it is coded into the type. So here
			 * modify the function bits based on the type.
			 */
		case AP_DEVICE_TYPE_CEX2A:
		case AP_DEVICE_TYPE_CEX3A:
			*facilities |= 0x08000000;
			break;
		case AP_DEVICE_TYPE_CEX2C:
		case AP_DEVICE_TYPE_CEX3C:
			*facilities |= 0x10000000;
			break;
		default:
			break;
		}
		return 0;
	case AP_RESPONSE_Q_NOT_AVAIL:
	case AP_RESPONSE_DECONFIGURED:
	case AP_RESPONSE_CHECKSTOPPED:
	case AP_RESPONSE_INVALID_ADDRESS:
		return -ENODEV;
	case AP_RESPONSE_RESET_IN_PROGRESS:
	case AP_RESPONSE_OTHERWISE_CHANGED:
	case AP_RESPONSE_BUSY:
		return -EBUSY;
	default:
		BUG();
	}
}