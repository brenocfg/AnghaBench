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
struct pmcmsptwi_cmd {int type; int write_len; int read_len; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 pmcmsptwi_cmd_to_reg(const struct pmcmsptwi_cmd *cmd)
{
	return ((cmd->type & 0x3) << 8) |
		(((cmd->write_len - 1) & 0x7) << 4) |
		((cmd->read_len - 1) & 0x7);
}