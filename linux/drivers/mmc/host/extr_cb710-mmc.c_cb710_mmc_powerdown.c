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
 int /*<<< orphan*/  CB710_MMC_CONFIG1_PORT ; 
 int /*<<< orphan*/  CB710_MMC_CONFIG3_PORT ; 
 int /*<<< orphan*/  cb710_modify_port_8 (struct cb710_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cb710_mmc_powerdown(struct cb710_slot *slot)
{
	cb710_modify_port_8(slot, CB710_MMC_CONFIG1_PORT, 0, 0x81);
	cb710_modify_port_8(slot, CB710_MMC_CONFIG3_PORT, 0, 0x80);
}