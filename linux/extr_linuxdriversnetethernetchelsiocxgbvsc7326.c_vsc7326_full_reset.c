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
 int /*<<< orphan*/  REG_SW_RESET ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vsc_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vsc7326_full_reset(adapter_t* adapter)
{
	u32 val;
	u32 result = 0xffff;

	t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val &= ~1;
	t1_tpi_write(adapter, A_ELMER0_GPO, val);
	udelay(2);
	val |= 0x1;	/* Enable mac MAC itself */
	val |= 0x800;	/* Turn off the red LED */
	t1_tpi_write(adapter, A_ELMER0_GPO, val);
	mdelay(1);
	vsc_write(adapter, REG_SW_RESET, 0x80000001);
	do {
		mdelay(1);
		vsc_read(adapter, REG_SW_RESET, &result);
	} while (result != 0x0);
}