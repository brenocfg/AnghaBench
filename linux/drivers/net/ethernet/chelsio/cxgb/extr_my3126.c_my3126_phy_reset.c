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
typedef  int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_GPO ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int my3126_phy_reset(adapter_t * adapter)
{
	u32 val;

	t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val &= ~4;
	t1_tpi_write(adapter, A_ELMER0_GPO, val);
	msleep(100);

	t1_tpi_write(adapter, A_ELMER0_GPO, val | 4);
	msleep(1000);

	/* Now lets enable the Laser. Delay 100us */
	t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val |= 0x8000;
	t1_tpi_write(adapter, A_ELMER0_GPO, val);
	udelay(100);
	return 0;
}