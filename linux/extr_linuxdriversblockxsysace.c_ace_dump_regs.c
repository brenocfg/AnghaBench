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
struct ace_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_BUSMODE ; 
 int /*<<< orphan*/  ACE_CFGLBA ; 
 int /*<<< orphan*/  ACE_CTRL ; 
 int /*<<< orphan*/  ACE_ERROR ; 
 int /*<<< orphan*/  ACE_FATSTAT ; 
 int /*<<< orphan*/  ACE_MPULBA ; 
 int /*<<< orphan*/  ACE_SECCNTCMD ; 
 int /*<<< orphan*/  ACE_STATUS ; 
 int /*<<< orphan*/  ACE_VERSION ; 
 int /*<<< orphan*/  ace_in (struct ace_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ace_in32 (struct ace_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ace_dump_regs(struct ace_device *ace)
{
	dev_info(ace->dev,
		 "    ctrl:  %.8x  seccnt/cmd: %.4x      ver:%.4x\n"
		 "    status:%.8x  mpu_lba:%.8x  busmode:%4x\n"
		 "    error: %.8x  cfg_lba:%.8x  fatstat:%.4x\n",
		 ace_in32(ace, ACE_CTRL),
		 ace_in(ace, ACE_SECCNTCMD),
		 ace_in(ace, ACE_VERSION),
		 ace_in32(ace, ACE_STATUS),
		 ace_in32(ace, ACE_MPULBA),
		 ace_in(ace, ACE_BUSMODE),
		 ace_in32(ace, ACE_ERROR),
		 ace_in32(ace, ACE_CFGLBA), ace_in(ace, ACE_FATSTAT));
}