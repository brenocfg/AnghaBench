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
typedef  int u16 ;

/* Variables and functions */
 int MV88E6XXX_PTP_TS_STATUS_MASK ; 
 int MV88E6XXX_PTP_TS_VALID ; 

__attribute__((used)) static int mv88e6xxx_ts_valid(u16 status)
{
	if (!(status & MV88E6XXX_PTP_TS_VALID))
		return 0;
	if (status & MV88E6XXX_PTP_TS_STATUS_MASK)
		return 0;
	return 1;
}