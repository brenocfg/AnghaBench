#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct lis3lv02d {scalar_t__ whoami; int (* read_data ) (struct lis3lv02d*,int /*<<< orphan*/ ) ;int scale; TYPE_1__ ac; int /*<<< orphan*/  (* blkread ) (struct lis3lv02d*,int /*<<< orphan*/ ,int,scalar_t__*) ;} ;
typedef  int s8 ;
typedef  int s16 ;

/* Variables and functions */
 int LIS3_ACCURACY ; 
 int /*<<< orphan*/  OUTX ; 
 int /*<<< orphan*/  OUTX_L ; 
 int /*<<< orphan*/  OUTY ; 
 int /*<<< orphan*/  OUTZ ; 
 scalar_t__ WAI_12B ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int lis3lv02d_get_axis (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (struct lis3lv02d*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (struct lis3lv02d*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int stub3 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 
 int stub4 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 
 int stub5 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lis3lv02d_get_xyz(struct lis3lv02d *lis3, int *x, int *y, int *z)
{
	int position[3];
	int i;

	if (lis3->blkread) {
		if (lis3->whoami == WAI_12B) {
			u16 data[3];
			lis3->blkread(lis3, OUTX_L, 6, (u8 *)data);
			for (i = 0; i < 3; i++)
				position[i] = (s16)le16_to_cpu(data[i]);
		} else {
			u8 data[5];
			/* Data: x, dummy, y, dummy, z */
			lis3->blkread(lis3, OUTX, 5, data);
			for (i = 0; i < 3; i++)
				position[i] = (s8)data[i * 2];
		}
	} else {
		position[0] = lis3->read_data(lis3, OUTX);
		position[1] = lis3->read_data(lis3, OUTY);
		position[2] = lis3->read_data(lis3, OUTZ);
	}

	for (i = 0; i < 3; i++)
		position[i] = (position[i] * lis3->scale) / LIS3_ACCURACY;

	*x = lis3lv02d_get_axis(lis3->ac.x, position);
	*y = lis3lv02d_get_axis(lis3->ac.y, position);
	*z = lis3lv02d_get_axis(lis3->ac.z, position);
}