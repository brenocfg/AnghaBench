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
struct max2175 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max2175_read (struct max2175*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max2175_write_bit (struct max2175*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_write_bits (struct max2175*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static u8 max2175_read_rom(struct max2175 *ctx, u8 row)
{
	u8 data = 0;

	max2175_write_bit(ctx, 56, 4, 0);
	max2175_write_bits(ctx, 56, 3, 0, row);

	usleep_range(2000, 2500);
	max2175_read(ctx, 58, &data);

	max2175_write_bits(ctx, 56, 3, 0, 0);

	mxm_dbg(ctx, "read_rom: row %d data 0x%02x\n", row, data);

	return data;
}