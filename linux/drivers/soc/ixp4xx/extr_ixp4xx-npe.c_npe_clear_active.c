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
struct npe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RD_ECS_REG ; 
 int /*<<< orphan*/  CMD_WR_ECS_REG ; 
 int ECS_REG_0_ACTIVE ; 
 int npe_cmd_read (struct npe*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npe_cmd_write (struct npe*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void npe_clear_active(struct npe *npe, u32 reg)
{
	u32 val = npe_cmd_read(npe, reg, CMD_RD_ECS_REG);
	npe_cmd_write(npe, reg, CMD_WR_ECS_REG, val & ~ECS_REG_0_ACTIVE);
}