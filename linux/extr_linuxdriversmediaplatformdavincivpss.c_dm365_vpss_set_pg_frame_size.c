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
struct vpss_pg_frame_size {int hlpfr; int pplen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM365_ISP5_PG_FRAME_SIZE ; 
 int /*<<< orphan*/  isp5_write (int,int /*<<< orphan*/ ) ; 

void dm365_vpss_set_pg_frame_size(struct vpss_pg_frame_size frame_size)
{
	int current_reg = ((frame_size.hlpfr >> 1) - 1) << 16;

	current_reg |= (frame_size.pplen - 1);
	isp5_write(current_reg, DM365_ISP5_PG_FRAME_SIZE);
}