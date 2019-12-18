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
typedef  unsigned int u8 ;
typedef  int u16 ;
struct cec_log_addrs {int num_log_addrs; char* osd_name; int vendor_id; scalar_t__ cec_version; int flags; int* log_addr_type; int* primary_device_type; unsigned int** features; int /*<<< orphan*/  log_addr_mask; scalar_t__* all_device_types; void** log_addr; } ;
struct TYPE_2__ {scalar_t__ unregistered; } ;
struct cec_adapter {int available_log_addrs; scalar_t__ phys_addr; struct cec_log_addrs log_addrs; TYPE_1__ devnode; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int CEC_LOG_ADDRS_FL_CDC_ONLY ; 
 void* CEC_LOG_ADDR_INVALID ; 
 int CEC_LOG_ADDR_TYPE_AUDIOSYSTEM ; 
 int CEC_LOG_ADDR_TYPE_PLAYBACK ; 
 int CEC_LOG_ADDR_TYPE_RECORD ; 
 int CEC_LOG_ADDR_TYPE_TV ; 
 int CEC_LOG_ADDR_TYPE_UNREGISTERED ; 
 int CEC_MAX_LOG_ADDRS ; 
 scalar_t__ CEC_OP_CEC_VERSION_1_4 ; 
 scalar_t__ CEC_OP_CEC_VERSION_2_0 ; 
 int CEC_OP_PRIM_DEVTYPE_PROCESSOR ; 
 int CEC_OP_PRIM_DEVTYPE_SWITCH ; 
 scalar_t__ CEC_PHYS_ADDR_INVALID ; 
 void* CEC_VENDOR_ID_NONE ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  cec_adap_unconfigure (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_claim_log_addrs (struct cec_adapter*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,unsigned int const) ; 

int __cec_s_log_addrs(struct cec_adapter *adap,
		      struct cec_log_addrs *log_addrs, bool block)
{
	u16 type_mask = 0;
	int i;

	if (adap->devnode.unregistered)
		return -ENODEV;

	if (!log_addrs || log_addrs->num_log_addrs == 0) {
		cec_adap_unconfigure(adap);
		adap->log_addrs.num_log_addrs = 0;
		for (i = 0; i < CEC_MAX_LOG_ADDRS; i++)
			adap->log_addrs.log_addr[i] = CEC_LOG_ADDR_INVALID;
		adap->log_addrs.osd_name[0] = '\0';
		adap->log_addrs.vendor_id = CEC_VENDOR_ID_NONE;
		adap->log_addrs.cec_version = CEC_OP_CEC_VERSION_2_0;
		return 0;
	}

	if (log_addrs->flags & CEC_LOG_ADDRS_FL_CDC_ONLY) {
		/*
		 * Sanitize log_addrs fields if a CDC-Only device is
		 * requested.
		 */
		log_addrs->num_log_addrs = 1;
		log_addrs->osd_name[0] = '\0';
		log_addrs->vendor_id = CEC_VENDOR_ID_NONE;
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_UNREGISTERED;
		/*
		 * This is just an internal convention since a CDC-Only device
		 * doesn't have to be a switch. But switches already use
		 * unregistered, so it makes some kind of sense to pick this
		 * as the primary device. Since a CDC-Only device never sends
		 * any 'normal' CEC messages this primary device type is never
		 * sent over the CEC bus.
		 */
		log_addrs->primary_device_type[0] = CEC_OP_PRIM_DEVTYPE_SWITCH;
		log_addrs->all_device_types[0] = 0;
		log_addrs->features[0][0] = 0;
		log_addrs->features[0][1] = 0;
	}

	/* Ensure the osd name is 0-terminated */
	log_addrs->osd_name[sizeof(log_addrs->osd_name) - 1] = '\0';

	/* Sanity checks */
	if (log_addrs->num_log_addrs > adap->available_log_addrs) {
		dprintk(1, "num_log_addrs > %d\n", adap->available_log_addrs);
		return -EINVAL;
	}

	/*
	 * Vendor ID is a 24 bit number, so check if the value is
	 * within the correct range.
	 */
	if (log_addrs->vendor_id != CEC_VENDOR_ID_NONE &&
	    (log_addrs->vendor_id & 0xff000000) != 0) {
		dprintk(1, "invalid vendor ID\n");
		return -EINVAL;
	}

	if (log_addrs->cec_version != CEC_OP_CEC_VERSION_1_4 &&
	    log_addrs->cec_version != CEC_OP_CEC_VERSION_2_0) {
		dprintk(1, "invalid CEC version\n");
		return -EINVAL;
	}

	if (log_addrs->num_log_addrs > 1)
		for (i = 0; i < log_addrs->num_log_addrs; i++)
			if (log_addrs->log_addr_type[i] ==
					CEC_LOG_ADDR_TYPE_UNREGISTERED) {
				dprintk(1, "num_log_addrs > 1 can't be combined with unregistered LA\n");
				return -EINVAL;
			}

	for (i = 0; i < log_addrs->num_log_addrs; i++) {
		const u8 feature_sz = ARRAY_SIZE(log_addrs->features[0]);
		u8 *features = log_addrs->features[i];
		bool op_is_dev_features = false;
		unsigned j;

		log_addrs->log_addr[i] = CEC_LOG_ADDR_INVALID;
		if (type_mask & (1 << log_addrs->log_addr_type[i])) {
			dprintk(1, "duplicate logical address type\n");
			return -EINVAL;
		}
		type_mask |= 1 << log_addrs->log_addr_type[i];
		if ((type_mask & (1 << CEC_LOG_ADDR_TYPE_RECORD)) &&
		    (type_mask & (1 << CEC_LOG_ADDR_TYPE_PLAYBACK))) {
			/* Record already contains the playback functionality */
			dprintk(1, "invalid record + playback combination\n");
			return -EINVAL;
		}
		if (log_addrs->primary_device_type[i] >
					CEC_OP_PRIM_DEVTYPE_PROCESSOR) {
			dprintk(1, "unknown primary device type\n");
			return -EINVAL;
		}
		if (log_addrs->primary_device_type[i] == 2) {
			dprintk(1, "invalid primary device type\n");
			return -EINVAL;
		}
		if (log_addrs->log_addr_type[i] > CEC_LOG_ADDR_TYPE_UNREGISTERED) {
			dprintk(1, "unknown logical address type\n");
			return -EINVAL;
		}
		for (j = 0; j < feature_sz; j++) {
			if ((features[j] & 0x80) == 0) {
				if (op_is_dev_features)
					break;
				op_is_dev_features = true;
			}
		}
		if (!op_is_dev_features || j == feature_sz) {
			dprintk(1, "malformed features\n");
			return -EINVAL;
		}
		/* Zero unused part of the feature array */
		memset(features + j + 1, 0, feature_sz - j - 1);
	}

	if (log_addrs->cec_version >= CEC_OP_CEC_VERSION_2_0) {
		if (log_addrs->num_log_addrs > 2) {
			dprintk(1, "CEC 2.0 allows no more than 2 logical addresses\n");
			return -EINVAL;
		}
		if (log_addrs->num_log_addrs == 2) {
			if (!(type_mask & ((1 << CEC_LOG_ADDR_TYPE_AUDIOSYSTEM) |
					   (1 << CEC_LOG_ADDR_TYPE_TV)))) {
				dprintk(1, "two LAs is only allowed for audiosystem and TV\n");
				return -EINVAL;
			}
			if (!(type_mask & ((1 << CEC_LOG_ADDR_TYPE_PLAYBACK) |
					   (1 << CEC_LOG_ADDR_TYPE_RECORD)))) {
				dprintk(1, "an audiosystem/TV can only be combined with record or playback\n");
				return -EINVAL;
			}
		}
	}

	/* Zero unused LAs */
	for (i = log_addrs->num_log_addrs; i < CEC_MAX_LOG_ADDRS; i++) {
		log_addrs->primary_device_type[i] = 0;
		log_addrs->log_addr_type[i] = 0;
		log_addrs->all_device_types[i] = 0;
		memset(log_addrs->features[i], 0,
		       sizeof(log_addrs->features[i]));
	}

	log_addrs->log_addr_mask = adap->log_addrs.log_addr_mask;
	adap->log_addrs = *log_addrs;
	if (adap->phys_addr != CEC_PHYS_ADDR_INVALID)
		cec_claim_log_addrs(adap, block);
	return 0;
}