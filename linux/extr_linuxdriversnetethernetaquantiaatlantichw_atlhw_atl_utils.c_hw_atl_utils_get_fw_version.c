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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aq_hw_read_reg (struct aq_hw_s*,int) ; 

int hw_atl_utils_get_fw_version(struct aq_hw_s *self, u32 *fw_version)
{
	*fw_version = aq_hw_read_reg(self, 0x18U);
	return 0;
}