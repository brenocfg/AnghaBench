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
struct realtek_smi {int dummy; } ;

/* Variables and functions */
 int realtek_smi_write_reg (struct realtek_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int realtek_smi_write_reg_noack(struct realtek_smi *smi, u32 addr,
				u32 data)
{
	return realtek_smi_write_reg(smi, addr, data, false);
}