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
struct adapter {int t1powersave; int /*<<< orphan*/  tpi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_GPO ; 
 int EALREADY ; 
 int ENODEV ; 
 int HCLOCK ; 
 int LCLOCK ; 
 int /*<<< orphan*/  __t1_tpi_read (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  __t1_tpi_write (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bit_bang (struct adapter*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_is_T1B (struct adapter*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int t1_clock(struct adapter *adapter, int mode)
{
	u32 val;
	int M_CORE_VAL;
	int M_MEM_VAL;

	enum {
		M_CORE_BITS	= 9,
		T_CORE_VAL	= 0,
		T_CORE_BITS	= 2,
		N_CORE_VAL	= 0,
		N_CORE_BITS	= 2,
		M_MEM_BITS	= 9,
		T_MEM_VAL	= 0,
		T_MEM_BITS	= 2,
		N_MEM_VAL	= 0,
		N_MEM_BITS	= 2,
		NP_LOAD		= 1 << 17,
		S_LOAD_MEM	= 1 << 5,
		S_LOAD_CORE	= 1 << 6,
		S_CLOCK		= 1 << 3
	};

	if (!t1_is_T1B(adapter))
		return -ENODEV;	/* Can't re-clock this chip. */

	if (mode & 2)
		return 0;	/* show current mode. */

	if ((adapter->t1powersave & 1) == (mode & 1))
		return -EALREADY;	/* ASIC already running in mode. */

	if ((mode & 1) == HCLOCK) {
		M_CORE_VAL = 0x14;
		M_MEM_VAL = 0x18;
		adapter->t1powersave = HCLOCK;	/* overclock */
	} else {
		M_CORE_VAL = 0xe;
		M_MEM_VAL = 0x10;
		adapter->t1powersave = LCLOCK;	/* underclock */
	}

	/* Don't interrupt this serial stream! */
	spin_lock(&adapter->tpi_lock);

	/* Initialize for ASIC core */
	__t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val |= NP_LOAD;
	udelay(50);
	__t1_tpi_write(adapter, A_ELMER0_GPO, val);
	udelay(50);
	__t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val &= ~S_LOAD_CORE;
	val &= ~S_CLOCK;
	__t1_tpi_write(adapter, A_ELMER0_GPO, val);
	udelay(50);

	/* Serial program the ASIC clock synthesizer */
	bit_bang(adapter, T_CORE_VAL, T_CORE_BITS);
	bit_bang(adapter, N_CORE_VAL, N_CORE_BITS);
	bit_bang(adapter, M_CORE_VAL, M_CORE_BITS);
	udelay(50);

	/* Finish ASIC core */
	__t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val |= S_LOAD_CORE;
	udelay(50);
	__t1_tpi_write(adapter, A_ELMER0_GPO, val);
	udelay(50);
	__t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val &= ~S_LOAD_CORE;
	udelay(50);
	__t1_tpi_write(adapter, A_ELMER0_GPO, val);
	udelay(50);

	/* Initialize for memory */
	__t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val |= NP_LOAD;
	udelay(50);
	__t1_tpi_write(adapter, A_ELMER0_GPO, val);
	udelay(50);
	__t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val &= ~S_LOAD_MEM;
	val &= ~S_CLOCK;
	udelay(50);
	__t1_tpi_write(adapter, A_ELMER0_GPO, val);
	udelay(50);

	/* Serial program the memory clock synthesizer */
	bit_bang(adapter, T_MEM_VAL, T_MEM_BITS);
	bit_bang(adapter, N_MEM_VAL, N_MEM_BITS);
	bit_bang(adapter, M_MEM_VAL, M_MEM_BITS);
	udelay(50);

	/* Finish memory */
	__t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val |= S_LOAD_MEM;
	udelay(50);
	__t1_tpi_write(adapter, A_ELMER0_GPO, val);
	udelay(50);
	__t1_tpi_read(adapter, A_ELMER0_GPO, &val);
	val &= ~S_LOAD_MEM;
	udelay(50);
	__t1_tpi_write(adapter, A_ELMER0_GPO, val);

	spin_unlock(&adapter->tpi_lock);

	return 0;
}