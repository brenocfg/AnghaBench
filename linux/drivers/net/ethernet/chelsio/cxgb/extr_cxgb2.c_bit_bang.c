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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_GPO ; 
 int /*<<< orphan*/  __t1_tpi_read (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  __t1_tpi_write (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bit_bang(struct adapter *adapter, int bitdata, int nbits)
{
	int data;
	int i;
	u32 val;

	enum {
		S_CLOCK = 1 << 3,
		S_DATA = 1 << 4
	};

	for (i = (nbits - 1); i > -1; i--) {

		udelay(50);

		data = ((bitdata >> i) & 0x1);
		__t1_tpi_read(adapter, A_ELMER0_GPO, &val);

		if (data)
			val |= S_DATA;
		else
			val &= ~S_DATA;

		udelay(50);

		/* Set SCLOCK low */
		val &= ~S_CLOCK;
		__t1_tpi_write(adapter, A_ELMER0_GPO, val);

		udelay(50);

		/* Write SCLOCK high */
		val |= S_CLOCK;
		__t1_tpi_write(adapter, A_ELMER0_GPO, val);

	}
}