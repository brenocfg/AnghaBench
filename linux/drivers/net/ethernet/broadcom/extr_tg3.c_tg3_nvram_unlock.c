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
struct tg3 {scalar_t__ nvram_lock_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVRAM ; 
 int /*<<< orphan*/  NVRAM_SWARB ; 
 int /*<<< orphan*/  SWARB_REQ_CLR1 ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_nvram_unlock(struct tg3 *tp)
{
	if (tg3_flag(tp, NVRAM)) {
		if (tp->nvram_lock_cnt > 0)
			tp->nvram_lock_cnt--;
		if (tp->nvram_lock_cnt == 0)
			tw32_f(NVRAM_SWARB, SWARB_REQ_CLR1);
	}
}