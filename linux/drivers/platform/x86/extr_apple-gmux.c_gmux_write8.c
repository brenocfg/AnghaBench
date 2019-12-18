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
typedef  int /*<<< orphan*/  u8 ;
struct apple_gmux_data {scalar_t__ indexed; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmux_index_write8 (struct apple_gmux_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmux_pio_write8 (struct apple_gmux_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gmux_write8(struct apple_gmux_data *gmux_data, int port, u8 val)
{
	if (gmux_data->indexed)
		gmux_index_write8(gmux_data, port, val);
	else
		gmux_pio_write8(gmux_data, port, val);
}