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
struct aq_hw_s {TYPE_1__* aq_nic_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  aq_hw_caps; } ;

/* Variables and functions */
 int hw_atl_utils_fw_rpc_init (struct aq_hw_s*) ; 
 int hw_atl_utils_init_ucp (struct aq_hw_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_atl_utils_mpi_create(struct aq_hw_s *self)
{
	int err = 0;

	err = hw_atl_utils_init_ucp(self, self->aq_nic_cfg->aq_hw_caps);
	if (err < 0)
		goto err_exit;

	err = hw_atl_utils_fw_rpc_init(self);
	if (err < 0)
		goto err_exit;

err_exit:
	return err;
}