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
struct dmcu {int dummy; } ;
struct dce_dmcu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCI_MEM_PWR_STATUS ; 
 int /*<<< orphan*/  DMCU_IRAM_MEM_PWR_STATE ; 
 int /*<<< orphan*/  DMCU_IRAM_WR_CTRL ; 
 int /*<<< orphan*/  DMCU_IRAM_WR_DATA ; 
 int /*<<< orphan*/  DMCU_RAM_ACCESS_CTRL ; 
 int /*<<< orphan*/  IRAM_HOST_ACCESS_EN ; 
 int /*<<< orphan*/  IRAM_WR_ADDR_AUTO_INC ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,char const) ; 
 struct dce_dmcu* TO_DCE_DMCU (struct dmcu*) ; 

bool dce_dmcu_load_iram(struct dmcu *dmcu,
		unsigned int start_offset,
		const char *src,
		unsigned int bytes)
{
	struct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	unsigned int count = 0;

	/* Enable write access to IRAM */
	REG_UPDATE_2(DMCU_RAM_ACCESS_CTRL,
			IRAM_HOST_ACCESS_EN, 1,
			IRAM_WR_ADDR_AUTO_INC, 1);

	REG_WAIT(DCI_MEM_PWR_STATUS, DMCU_IRAM_MEM_PWR_STATE, 0, 2, 10);

	REG_WRITE(DMCU_IRAM_WR_CTRL, start_offset);

	for (count = 0; count < bytes; count++)
		REG_WRITE(DMCU_IRAM_WR_DATA, src[count]);

	/* Disable write access to IRAM to allow dynamic sleep state */
	REG_UPDATE_2(DMCU_RAM_ACCESS_CTRL,
			IRAM_HOST_ACCESS_EN, 0,
			IRAM_WR_ADDR_AUTO_INC, 0);

	return true;
}