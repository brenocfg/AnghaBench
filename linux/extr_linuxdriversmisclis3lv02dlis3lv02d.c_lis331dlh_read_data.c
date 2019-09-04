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
struct lis3lv02d {int shift_adj; int /*<<< orphan*/  (* read ) (struct lis3lv02d*,int,int*) ;} ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct lis3lv02d*,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct lis3lv02d*,int,int*) ; 

__attribute__((used)) static s16 lis331dlh_read_data(struct lis3lv02d *lis3, int reg)
{
	u8 lo, hi;
	int v;

	lis3->read(lis3, reg - 1, &lo);
	lis3->read(lis3, reg, &hi);
	v = (int) ((hi << 8) | lo);

	return (s16) v >> lis3->shift_adj;
}