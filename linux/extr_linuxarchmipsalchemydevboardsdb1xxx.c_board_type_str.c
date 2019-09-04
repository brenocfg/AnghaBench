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
 int /*<<< orphan*/  BCSR_WHOAMI ; 
 int BCSR_WHOAMI_BOARD (int /*<<< orphan*/ ) ; 
#define  BCSR_WHOAMI_DB1000 140 
#define  BCSR_WHOAMI_DB1100 139 
#define  BCSR_WHOAMI_DB1200 138 
#define  BCSR_WHOAMI_DB1300 137 
#define  BCSR_WHOAMI_DB1500 136 
#define  BCSR_WHOAMI_DB1550 135 
#define  BCSR_WHOAMI_PB1100 134 
#define  BCSR_WHOAMI_PB1200_DDR1 133 
#define  BCSR_WHOAMI_PB1200_DDR2 132 
#define  BCSR_WHOAMI_PB1500 131 
#define  BCSR_WHOAMI_PB1500R2 130 
#define  BCSR_WHOAMI_PB1550_DDR 129 
#define  BCSR_WHOAMI_PB1550_SDR 128 
 int /*<<< orphan*/  bcsr_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *board_type_str(void)
{
	switch (BCSR_WHOAMI_BOARD(bcsr_read(BCSR_WHOAMI))) {
	case BCSR_WHOAMI_DB1000:
		return "DB1000";
	case BCSR_WHOAMI_DB1500:
		return "DB1500";
	case BCSR_WHOAMI_DB1100:
		return "DB1100";
	case BCSR_WHOAMI_PB1500:
	case BCSR_WHOAMI_PB1500R2:
		return "PB1500";
	case BCSR_WHOAMI_PB1100:
		return "PB1100";
	case BCSR_WHOAMI_PB1200_DDR1:
	case BCSR_WHOAMI_PB1200_DDR2:
		return "PB1200";
	case BCSR_WHOAMI_DB1200:
		return "DB1200";
	case BCSR_WHOAMI_DB1300:
		return "DB1300";
	case BCSR_WHOAMI_DB1550:
		return "DB1550";
	case BCSR_WHOAMI_PB1550_SDR:
	case BCSR_WHOAMI_PB1550_DDR:
		return "PB1550";
	default:
		return "(unknown)";
	}
}