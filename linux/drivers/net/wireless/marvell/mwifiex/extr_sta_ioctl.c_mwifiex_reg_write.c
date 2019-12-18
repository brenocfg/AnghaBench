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
typedef  void* u32 ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_ds_reg_rw {void* value; void* offset; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int mwifiex_reg_mem_ioctl_reg_rw (struct mwifiex_private*,struct mwifiex_ds_reg_rw*,int /*<<< orphan*/ ) ; 

int
mwifiex_reg_write(struct mwifiex_private *priv, u32 reg_type,
		  u32 reg_offset, u32 reg_value)
{
	struct mwifiex_ds_reg_rw reg_rw;

	reg_rw.type = reg_type;
	reg_rw.offset = reg_offset;
	reg_rw.value = reg_value;

	return mwifiex_reg_mem_ioctl_reg_rw(priv, &reg_rw, HostCmd_ACT_GEN_SET);
}