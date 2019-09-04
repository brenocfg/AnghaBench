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

/* Variables and functions */
 int /*<<< orphan*/  HPET_CFG ; 
 unsigned int HPET_CFG_ENABLE ; 
 unsigned int hpet_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_write (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void hpet_stop_counter(void)
{
	unsigned int cfg = hpet_read(HPET_CFG);

	cfg &= ~HPET_CFG_ENABLE;
	hpet_write(HPET_CFG, cfg);
}