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
typedef  int /*<<< orphan*/  u32 ;
struct hw_atl_utils_mbox_header {int dummy; } ;
struct aq_hw_s {int /*<<< orphan*/  mbox_addr; } ;

/* Variables and functions */
 int hw_atl_utils_fw_downld_dwords (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int hw_atl_utils_mpi_read_mbox(struct aq_hw_s *self,
			       struct hw_atl_utils_mbox_header *pmbox)
{
	return hw_atl_utils_fw_downld_dwords(self,
					     self->mbox_addr,
					     (u32 *)(void *)pmbox,
					     sizeof(*pmbox) / sizeof(u32));
}