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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */
 int nlm_read_sata_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_write_sata_reg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void sata_set_glue_reg(u64 regbase, u32 off, u32 bit)
{
	u32 reg_val;

	reg_val = nlm_read_sata_reg(regbase, off);
	nlm_write_sata_reg(regbase, off, (reg_val | bit));
}