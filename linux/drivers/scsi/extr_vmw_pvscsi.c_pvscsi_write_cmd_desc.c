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
typedef  int /*<<< orphan*/  const u32 ;
struct pvscsi_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_COMMAND ; 
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_COMMAND_DATA ; 
 int /*<<< orphan*/  pvscsi_reg_write (struct pvscsi_adapter const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void pvscsi_write_cmd_desc(const struct pvscsi_adapter *adapter,
				  u32 cmd, const void *desc, size_t len)
{
	const u32 *ptr = desc;
	size_t i;

	len /= sizeof(*ptr);
	pvscsi_reg_write(adapter, PVSCSI_REG_OFFSET_COMMAND, cmd);
	for (i = 0; i < len; i++)
		pvscsi_reg_write(adapter,
				 PVSCSI_REG_OFFSET_COMMAND_DATA, ptr[i]);
}