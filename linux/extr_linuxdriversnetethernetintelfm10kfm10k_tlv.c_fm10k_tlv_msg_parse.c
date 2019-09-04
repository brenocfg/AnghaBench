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
typedef  int u32 ;
struct fm10k_msg_data {int id; scalar_t__ (* func ) (struct fm10k_hw*,int**,struct fm10k_mbx_info*) ;int /*<<< orphan*/  attr; } ;
struct fm10k_mbx_info {int dummy; } ;
struct fm10k_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FM10K_ERR_PARAM ; 
 int FM10K_TLV_ERROR ; 
 int FM10K_TLV_FLAGS_MSG ; 
 int FM10K_TLV_FLAGS_SHIFT ; 
 int FM10K_TLV_ID_MASK ; 
 int FM10K_TLV_RESULTS_MAX ; 
 scalar_t__ fm10k_tlv_attr_parse (int*,int**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct fm10k_hw*,int**,struct fm10k_mbx_info*) ; 

s32 fm10k_tlv_msg_parse(struct fm10k_hw *hw, u32 *msg,
			struct fm10k_mbx_info *mbx,
			const struct fm10k_msg_data *data)
{
	u32 *results[FM10K_TLV_RESULTS_MAX];
	u32 msg_id;
	s32 err;

	/* verify pointer is not NULL */
	if (!msg || !data)
		return FM10K_ERR_PARAM;

	/* verify this is a message and not an attribute */
	if (!(*msg & (FM10K_TLV_FLAGS_MSG << FM10K_TLV_FLAGS_SHIFT)))
		return FM10K_ERR_PARAM;

	/* grab message ID */
	msg_id = *msg & FM10K_TLV_ID_MASK;

	while (data->id < msg_id)
		data++;

	/* if we didn't find it then pass it up as an error */
	if (data->id != msg_id) {
		while (data->id != FM10K_TLV_ERROR)
			data++;
	}

	/* parse the attributes into the results list */
	err = fm10k_tlv_attr_parse(msg, results, data->attr);
	if (err < 0)
		return err;

	return data->func(hw, results, mbx);
}