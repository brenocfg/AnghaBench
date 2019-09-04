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
struct mem_ctl_info {int dummy; } ;
struct err_info {int err_code; int /*<<< orphan*/  channel; int /*<<< orphan*/  csrow; int /*<<< orphan*/  syndrome; int /*<<< orphan*/  offset; int /*<<< orphan*/  page; } ;
typedef  enum hw_event_mc_err_type { ____Placeholder_hw_event_mc_err_type } hw_event_mc_err_type ;

/* Variables and functions */
#define  DECODE_OK 133 
#define  ERR_CHANNEL 132 
#define  ERR_CSROW 131 
#define  ERR_NODE 130 
#define  ERR_NORM_ADDR 129 
#define  ERR_SYND 128 
 int HW_EVENT_ERR_CORRECTED ; 
 int HW_EVENT_ERR_DEFERRED ; 
 int HW_EVENT_ERR_UNCORRECTED ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int,struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,char*) ; 

__attribute__((used)) static void __log_ecc_error(struct mem_ctl_info *mci, struct err_info *err,
			    u8 ecc_type)
{
	enum hw_event_mc_err_type err_type;
	const char *string;

	if (ecc_type == 2)
		err_type = HW_EVENT_ERR_CORRECTED;
	else if (ecc_type == 1)
		err_type = HW_EVENT_ERR_UNCORRECTED;
	else if (ecc_type == 3)
		err_type = HW_EVENT_ERR_DEFERRED;
	else {
		WARN(1, "Something is rotten in the state of Denmark.\n");
		return;
	}

	switch (err->err_code) {
	case DECODE_OK:
		string = "";
		break;
	case ERR_NODE:
		string = "Failed to map error addr to a node";
		break;
	case ERR_CSROW:
		string = "Failed to map error addr to a csrow";
		break;
	case ERR_CHANNEL:
		string = "Unknown syndrome - possible error reporting race";
		break;
	case ERR_SYND:
		string = "MCA_SYND not valid - unknown syndrome and csrow";
		break;
	case ERR_NORM_ADDR:
		string = "Cannot decode normalized address";
		break;
	default:
		string = "WTF error";
		break;
	}

	edac_mc_handle_error(err_type, mci, 1,
			     err->page, err->offset, err->syndrome,
			     err->csrow, err->channel, -1,
			     string, "");
}