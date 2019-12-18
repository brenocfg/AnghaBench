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
typedef  int u8 ;
struct cec_msg {int* msg; int len; } ;
struct cec_log_addrs {int** features; int* log_addr; int cec_version; int* all_device_types; } ;
struct cec_adapter {struct cec_log_addrs log_addrs; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int CEC_MSG_REPORT_FEATURES ; 
 int const CEC_OP_FEAT_EXT ; 

__attribute__((used)) static void cec_fill_msg_report_features(struct cec_adapter *adap,
					 struct cec_msg *msg,
					 unsigned int la_idx)
{
	const struct cec_log_addrs *las = &adap->log_addrs;
	const u8 *features = las->features[la_idx];
	bool op_is_dev_features = false;
	unsigned int idx;

	/* Report Features */
	msg->msg[0] = (las->log_addr[la_idx] << 4) | 0x0f;
	msg->len = 4;
	msg->msg[1] = CEC_MSG_REPORT_FEATURES;
	msg->msg[2] = adap->log_addrs.cec_version;
	msg->msg[3] = las->all_device_types[la_idx];

	/* Write RC Profiles first, then Device Features */
	for (idx = 0; idx < ARRAY_SIZE(las->features[0]); idx++) {
		msg->msg[msg->len++] = features[idx];
		if ((features[idx] & CEC_OP_FEAT_EXT) == 0) {
			if (op_is_dev_features)
				break;
			op_is_dev_features = true;
		}
	}
}