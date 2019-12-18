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
struct TYPE_2__ {int async_reset; } ;
struct lima_ip {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_GP_CMD ; 
 int /*<<< orphan*/  LIMA_GP_CMD_SOFT_RESET ; 
 int /*<<< orphan*/  LIMA_GP_INT_CLEAR ; 
 int /*<<< orphan*/  LIMA_GP_INT_MASK ; 
 int /*<<< orphan*/  LIMA_GP_IRQ_RESET_COMPLETED ; 
 int /*<<< orphan*/  gp_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lima_gp_soft_reset_async(struct lima_ip *ip)
{
	if (ip->data.async_reset)
		return;

	gp_write(LIMA_GP_INT_MASK, 0);
	gp_write(LIMA_GP_INT_CLEAR, LIMA_GP_IRQ_RESET_COMPLETED);
	gp_write(LIMA_GP_CMD, LIMA_GP_CMD_SOFT_RESET);
	ip->data.async_reset = true;
}