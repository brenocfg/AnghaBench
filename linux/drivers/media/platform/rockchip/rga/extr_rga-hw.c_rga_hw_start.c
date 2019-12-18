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
struct rockchip_rga {struct rga_ctx* curr; } ;
struct rga_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGA_CMD_CTRL ; 
 int /*<<< orphan*/  RGA_INT ; 
 int /*<<< orphan*/  RGA_SYS_CTRL ; 
 int /*<<< orphan*/  rga_cmd_set (struct rga_ctx*) ; 
 int /*<<< orphan*/  rga_write (struct rockchip_rga*,int /*<<< orphan*/ ,int) ; 

void rga_hw_start(struct rockchip_rga *rga)
{
	struct rga_ctx *ctx = rga->curr;

	rga_cmd_set(ctx);

	rga_write(rga, RGA_SYS_CTRL, 0x00);

	rga_write(rga, RGA_SYS_CTRL, 0x22);

	rga_write(rga, RGA_INT, 0x600);

	rga_write(rga, RGA_CMD_CTRL, 0x1);
}