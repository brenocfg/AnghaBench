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
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_STATUS ; 
 int /*<<< orphan*/  sd_ctrl_write32_as_16_and_16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tmio_mmc_ack_mmc_irqs(struct tmio_mmc_host *host, u32 i)
{
	sd_ctrl_write32_as_16_and_16(host, CTL_STATUS, ~i);
}