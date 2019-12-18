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
struct fm10k_tlv_attr {unsigned int id; } ;
struct fm10k_msg_data {unsigned int id; int /*<<< orphan*/  func; struct fm10k_tlv_attr* attr; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 unsigned int FM10K_TLV_ERROR ; 
 unsigned int FM10K_TLV_RESULTS_MAX ; 

__attribute__((used)) static s32 fm10k_mbx_validate_handlers(const struct fm10k_msg_data *msg_data)
{
	const struct fm10k_tlv_attr *attr;
	unsigned int id;

	/* Allow NULL mailboxes that transmit but don't receive */
	if (!msg_data)
		return 0;

	while (msg_data->id != FM10K_TLV_ERROR) {
		/* all messages should have a function handler */
		if (!msg_data->func)
			return FM10K_ERR_PARAM;

		/* parser is optional */
		attr = msg_data->attr;
		if (attr) {
			while (attr->id != FM10K_TLV_ERROR) {
				id = attr->id;
				attr++;
				/* ID should always be increasing */
				if (id >= attr->id)
					return FM10K_ERR_PARAM;
				/* ID should fit in results array */
				if (id >= FM10K_TLV_RESULTS_MAX)
					return FM10K_ERR_PARAM;
			}

			/* verify terminator is in the list */
			if (attr->id != FM10K_TLV_ERROR)
				return FM10K_ERR_PARAM;
		}

		id = msg_data->id;
		msg_data++;
		/* ID should always be increasing */
		if (id >= msg_data->id)
			return FM10K_ERR_PARAM;
	}

	/* verify terminator is in the list */
	if ((msg_data->id != FM10K_TLV_ERROR) || !msg_data->func)
		return FM10K_ERR_PARAM;

	return 0;
}