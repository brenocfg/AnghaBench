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
struct cb710_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_MMC_STATUS0_PORT ; 
 int /*<<< orphan*/  CB710_MMC_STATUS1_PORT ; 
 int /*<<< orphan*/  CB710_MMC_STATUS2_PORT ; 
 int /*<<< orphan*/  cb710_write_port_8 (struct cb710_slot*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cb710_mmc_reset_events(struct cb710_slot *slot)
{
	cb710_write_port_8(slot, CB710_MMC_STATUS0_PORT, 0xFF);
	cb710_write_port_8(slot, CB710_MMC_STATUS1_PORT, 0xFF);
	cb710_write_port_8(slot, CB710_MMC_STATUS2_PORT, 0xFF);
}