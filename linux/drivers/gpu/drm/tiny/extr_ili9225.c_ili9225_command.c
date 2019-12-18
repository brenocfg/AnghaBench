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
typedef  int u8 ;
typedef  int u16 ;
struct mipi_dbi {int dummy; } ;

/* Variables and functions */
 int mipi_dbi_command_buf (struct mipi_dbi*,int,int*,int) ; 

__attribute__((used)) static inline int ili9225_command(struct mipi_dbi *dbi, u8 cmd, u16 data)
{
	u8 par[2] = { data >> 8, data & 0xff };

	return mipi_dbi_command_buf(dbi, cmd, par, 2);
}