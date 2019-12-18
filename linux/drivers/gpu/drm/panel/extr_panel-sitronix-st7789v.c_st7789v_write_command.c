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
struct st7789v {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST7789V_COMMAND ; 
 int st7789v_spi_write (struct st7789v*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st7789v_write_command(struct st7789v *ctx, u8 cmd)
{
	return st7789v_spi_write(ctx, ST7789V_COMMAND, cmd);
}