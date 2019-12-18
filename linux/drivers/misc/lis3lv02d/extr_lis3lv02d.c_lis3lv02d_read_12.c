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
struct lis3lv02d {int /*<<< orphan*/  (* read ) (struct lis3lv02d*,int,int*) ;} ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct lis3lv02d*,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct lis3lv02d*,int,int*) ; 

__attribute__((used)) static s16 lis3lv02d_read_12(struct lis3lv02d *lis3, int reg)
{
	u8 lo, hi;

	lis3->read(lis3, reg - 1, &lo);
	lis3->read(lis3, reg, &hi);
	/* In "12 bit right justified" mode, bit 6, bit 7, bit 8 = bit 5 */
	return (s16)((hi << 8) | lo);
}