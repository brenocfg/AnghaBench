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
struct iavf_hw {int dummy; } ;
struct iavf_aqc_queue_shutdown {int /*<<< orphan*/  driver_unloading; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct iavf_aq_desc {TYPE_1__ params; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_AQ_DRIVER_UNLOADING ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_aqc_opc_queue_shutdown ; 
 int iavf_asq_send_command (struct iavf_hw*,struct iavf_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iavf_fill_default_direct_cmd_desc (struct iavf_aq_desc*,int /*<<< orphan*/ ) ; 

enum iavf_status iavf_aq_queue_shutdown(struct iavf_hw *hw, bool unloading)
{
	struct iavf_aq_desc desc;
	struct iavf_aqc_queue_shutdown *cmd =
		(struct iavf_aqc_queue_shutdown *)&desc.params.raw;
	enum iavf_status status;

	iavf_fill_default_direct_cmd_desc(&desc, iavf_aqc_opc_queue_shutdown);

	if (unloading)
		cmd->driver_unloading = cpu_to_le32(IAVF_AQ_DRIVER_UNLOADING);
	status = iavf_asq_send_command(hw, &desc, NULL, 0, NULL);

	return status;
}