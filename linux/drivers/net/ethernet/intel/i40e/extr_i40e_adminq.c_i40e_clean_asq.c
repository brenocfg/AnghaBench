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
typedef  scalar_t__ u16 ;
struct i40e_adminq_ring {scalar_t__ next_to_clean; scalar_t__ count; int /*<<< orphan*/  head; } ;
struct TYPE_2__ {struct i40e_adminq_ring asq; } ;
struct i40e_hw {TYPE_1__ aq; } ;
struct i40e_asq_cmd_details {scalar_t__ callback; } ;
struct i40e_aq_desc {scalar_t__ callback; } ;
typedef  int /*<<< orphan*/  (* I40E_ADMINQ_CALLBACK ) (struct i40e_hw*,struct i40e_asq_cmd_details*) ;

/* Variables and functions */
 struct i40e_asq_cmd_details* I40E_ADMINQ_DESC (struct i40e_adminq_ring,scalar_t__) ; 
 struct i40e_asq_cmd_details* I40E_ADMINQ_DETAILS (struct i40e_adminq_ring,scalar_t__) ; 
 int /*<<< orphan*/  I40E_DEBUG_AQ_COMMAND ; 
 scalar_t__ I40E_DESC_UNUSED (struct i40e_adminq_ring*) ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct i40e_asq_cmd_details*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 i40e_clean_asq(struct i40e_hw *hw)
{
	struct i40e_adminq_ring *asq = &(hw->aq.asq);
	struct i40e_asq_cmd_details *details;
	u16 ntc = asq->next_to_clean;
	struct i40e_aq_desc desc_cb;
	struct i40e_aq_desc *desc;

	desc = I40E_ADMINQ_DESC(*asq, ntc);
	details = I40E_ADMINQ_DETAILS(*asq, ntc);
	while (rd32(hw, hw->aq.asq.head) != ntc) {
		i40e_debug(hw, I40E_DEBUG_AQ_COMMAND,
			   "ntc %d head %d.\n", ntc, rd32(hw, hw->aq.asq.head));

		if (details->callback) {
			I40E_ADMINQ_CALLBACK cb_func =
					(I40E_ADMINQ_CALLBACK)details->callback;
			desc_cb = *desc;
			cb_func(hw, &desc_cb);
		}
		memset(desc, 0, sizeof(*desc));
		memset(details, 0, sizeof(*details));
		ntc++;
		if (ntc == asq->count)
			ntc = 0;
		desc = I40E_ADMINQ_DESC(*asq, ntc);
		details = I40E_ADMINQ_DETAILS(*asq, ntc);
	}

	asq->next_to_clean = ntc;

	return I40E_DESC_UNUSED(asq);
}