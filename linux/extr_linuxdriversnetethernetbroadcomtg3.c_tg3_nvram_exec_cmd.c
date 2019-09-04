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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NVRAM_CMD ; 
 int NVRAM_CMD_DONE ; 
 int NVRAM_CMD_TIMEOUT ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tg3_nvram_exec_cmd(struct tg3 *tp, u32 nvram_cmd)
{
	int i;

	tw32(NVRAM_CMD, nvram_cmd);
	for (i = 0; i < NVRAM_CMD_TIMEOUT; i++) {
		usleep_range(10, 40);
		if (tr32(NVRAM_CMD) & NVRAM_CMD_DONE) {
			udelay(10);
			break;
		}
	}

	if (i == NVRAM_CMD_TIMEOUT)
		return -EBUSY;

	return 0;
}