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
typedef  int /*<<< orphan*/  u32 ;
struct apple_gmux_data {scalar_t__ indexed; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmux_index_read32 (struct apple_gmux_data*,int) ; 
 int /*<<< orphan*/  gmux_pio_read32 (struct apple_gmux_data*,int) ; 

__attribute__((used)) static u32 gmux_read32(struct apple_gmux_data *gmux_data, int port)
{
	if (gmux_data->indexed)
		return gmux_index_read32(gmux_data, port);
	else
		return gmux_pio_read32(gmux_data, port);
}