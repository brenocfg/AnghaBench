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
struct board_info {int board; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_GPO ; 
#define  CHBT_BOARD_7500 138 
#define  CHBT_BOARD_8000 137 
#define  CHBT_BOARD_CHN204 136 
#define  CHBT_BOARD_CHT101 135 
#define  CHBT_BOARD_CHT110 134 
#define  CHBT_BOARD_CHT204 133 
#define  CHBT_BOARD_CHT204E 132 
#define  CHBT_BOARD_CHT204V 131 
#define  CHBT_BOARD_CHT210 130 
#define  CHBT_BOARD_N110 129 
#define  CHBT_BOARD_N210 128 
 int /*<<< orphan*/  power_sequence_xpak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_tpi_par (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int board_init(adapter_t *adapter, const struct board_info *bi)
{
	switch (bi->board) {
	case CHBT_BOARD_8000:
	case CHBT_BOARD_N110:
	case CHBT_BOARD_N210:
	case CHBT_BOARD_CHT210:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_write(adapter, A_ELMER0_GPO, 0x800);
		break;
	case CHBT_BOARD_CHT110:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_write(adapter, A_ELMER0_GPO, 0x1800);

		/* TBD XXX Might not need.  This fixes a problem
		 *         described in the Intel SR XPAK errata.
		 */
		power_sequence_xpak(adapter);
		break;
#ifdef CONFIG_CHELSIO_T1_1G
	case CHBT_BOARD_CHT204E:
		/* add config space write here */
	case CHBT_BOARD_CHT204:
	case CHBT_BOARD_CHT204V:
	case CHBT_BOARD_CHN204:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_write(adapter, A_ELMER0_GPO, 0x804);
		break;
	case CHBT_BOARD_CHT101:
	case CHBT_BOARD_7500:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_write(adapter, A_ELMER0_GPO, 0x1804);
		break;
#endif
	}
	return 0;
}