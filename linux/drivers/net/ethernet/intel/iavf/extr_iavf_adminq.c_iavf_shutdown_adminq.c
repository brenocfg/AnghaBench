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
 int /*<<< orphan*/  iavf_aq_queue_shutdown (struct iavf_hw*,int) ; 
 scalar_t__ iavf_check_asq_alive (struct iavf_hw*) ; 
 int /*<<< orphan*/  iavf_shutdown_arq (struct iavf_hw*) ; 
 int /*<<< orphan*/  iavf_shutdown_asq (struct iavf_hw*) ; 

enum iavf_status iavf_shutdown_adminq(struct iavf_hw *hw)
{
	enum iavf_status ret_code = 0;

	if (iavf_check_asq_alive(hw))
		iavf_aq_queue_shutdown(hw, true);

	iavf_shutdown_asq(hw);
	iavf_shutdown_arq(hw);

	return ret_code;
}