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
struct lg4573 {int dummy; } ;

/* Variables and functions */
 int lg4573_spi_write_u16 (struct lg4573*,int) ; 

__attribute__((used)) static int lg4573_spi_write_dcs(struct lg4573 *ctx, u8 dcs)
{
	return lg4573_spi_write_u16(ctx, (0x70 << 8 | dcs));
}