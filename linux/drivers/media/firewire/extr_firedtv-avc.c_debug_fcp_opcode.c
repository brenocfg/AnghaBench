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

/* Variables and functions */
 int AVC_DEBUG_CA2HOST ; 
 int AVC_DEBUG_DSD ; 
 int AVC_DEBUG_DSIT ; 
 int AVC_DEBUG_HOST2CA ; 
 int AVC_DEBUG_LNB_CONTROL ; 
 int AVC_DEBUG_READ_DESCRIPTOR ; 
 int AVC_DEBUG_REGISTER_REMOTE_CONTROL ; 
 int AVC_DEBUG_TUNE_QPSK ; 
 int AVC_DEBUG_TUNE_QPSK2 ; 
#define  AVC_OPCODE_DSD 137 
#define  AVC_OPCODE_DSIT 136 
#define  AVC_OPCODE_READ_DESCRIPTOR 135 
#define  AVC_OPCODE_VENDOR 134 
 int const SFE_VENDOR_DE_COMPANYID_0 ; 
 int const SFE_VENDOR_DE_COMPANYID_1 ; 
 int const SFE_VENDOR_DE_COMPANYID_2 ; 
#define  SFE_VENDOR_OPCODE_CA2HOST 133 
#define  SFE_VENDOR_OPCODE_HOST2CA 132 
#define  SFE_VENDOR_OPCODE_LNB_CONTROL 131 
#define  SFE_VENDOR_OPCODE_REGISTER_REMOTE_CONTROL 130 
#define  SFE_VENDOR_OPCODE_TUNE_QPSK 129 
#define  SFE_VENDOR_OPCODE_TUNE_QPSK2 128 
 int avc_debug ; 

__attribute__((used)) static const char *debug_fcp_opcode(unsigned int opcode,
				    const u8 *data, int length)
{
	switch (opcode) {
	case AVC_OPCODE_VENDOR:
		break;
	case AVC_OPCODE_READ_DESCRIPTOR:
		return avc_debug & AVC_DEBUG_READ_DESCRIPTOR ?
				"ReadDescriptor" : NULL;
	case AVC_OPCODE_DSIT:
		return avc_debug & AVC_DEBUG_DSIT ?
				"DirectSelectInfo.Type" : NULL;
	case AVC_OPCODE_DSD:
		return avc_debug & AVC_DEBUG_DSD ? "DirectSelectData" : NULL;
	default:
		return "Unknown";
	}

	if (length < 7 ||
	    data[3] != SFE_VENDOR_DE_COMPANYID_0 ||
	    data[4] != SFE_VENDOR_DE_COMPANYID_1 ||
	    data[5] != SFE_VENDOR_DE_COMPANYID_2)
		return "Vendor/Unknown";

	switch (data[6]) {
	case SFE_VENDOR_OPCODE_REGISTER_REMOTE_CONTROL:
		return avc_debug & AVC_DEBUG_REGISTER_REMOTE_CONTROL ?
				"RegisterRC" : NULL;
	case SFE_VENDOR_OPCODE_LNB_CONTROL:
		return avc_debug & AVC_DEBUG_LNB_CONTROL ? "LNBControl" : NULL;
	case SFE_VENDOR_OPCODE_TUNE_QPSK:
		return avc_debug & AVC_DEBUG_TUNE_QPSK ? "TuneQPSK" : NULL;
	case SFE_VENDOR_OPCODE_TUNE_QPSK2:
		return avc_debug & AVC_DEBUG_TUNE_QPSK2 ? "TuneQPSK2" : NULL;
	case SFE_VENDOR_OPCODE_HOST2CA:
		return avc_debug & AVC_DEBUG_HOST2CA ? "Host2CA" : NULL;
	case SFE_VENDOR_OPCODE_CA2HOST:
		return avc_debug & AVC_DEBUG_CA2HOST ? "CA2Host" : NULL;
	}
	return "Vendor/Unknown";
}