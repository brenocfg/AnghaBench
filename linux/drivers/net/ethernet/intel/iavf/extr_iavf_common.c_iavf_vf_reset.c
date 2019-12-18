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
struct iavf_hw {int dummy; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTCHNL_OP_RESET_VF ; 
 int iavf_aq_send_msg_to_pf (struct iavf_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

enum iavf_status iavf_vf_reset(struct iavf_hw *hw)
{
	return iavf_aq_send_msg_to_pf(hw, VIRTCHNL_OP_RESET_VF,
				      0, NULL, 0, NULL);
}