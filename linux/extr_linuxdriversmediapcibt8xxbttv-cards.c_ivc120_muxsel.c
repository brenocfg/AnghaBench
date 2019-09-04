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
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_TDA8540_ALT3 ; 
 int /*<<< orphan*/  I2C_TDA8540_ALT4 ; 
 int /*<<< orphan*/  I2C_TDA8540_ALT5 ; 
 int /*<<< orphan*/  I2C_TDA8540_ALT6 ; 
 int /*<<< orphan*/  bttv_I2CWrite (struct bttv*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned int,int,int) ; 

__attribute__((used)) static void ivc120_muxsel(struct bttv *btv, unsigned int input)
{
	/* Simple maths */
	int key = input % 4;
	int matrix = input / 4;

	dprintk("%d: ivc120_muxsel: Input - %02d | TDA - %02d | In - %02d\n",
		btv->c.nr, input, matrix, key);

	/* Handles the input selection on the TDA8540's */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT3, 0x00,
		      ((matrix == 3) ? (key | key << 2) : 0x00), 1);
	bttv_I2CWrite(btv, I2C_TDA8540_ALT4, 0x00,
		      ((matrix == 0) ? (key | key << 2) : 0x00), 1);
	bttv_I2CWrite(btv, I2C_TDA8540_ALT5, 0x00,
		      ((matrix == 1) ? (key | key << 2) : 0x00), 1);
	bttv_I2CWrite(btv, I2C_TDA8540_ALT6, 0x00,
		      ((matrix == 2) ? (key | key << 2) : 0x00), 1);

	/* Handles the output enables on the TDA8540's */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT3, 0x02,
		      ((matrix == 3) ? 0x03 : 0x00), 1);  /* 13 - 16 */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT4, 0x02,
		      ((matrix == 0) ? 0x03 : 0x00), 1);  /* 1-4 */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT5, 0x02,
		      ((matrix == 1) ? 0x03 : 0x00), 1);  /* 5-8 */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT6, 0x02,
		      ((matrix == 2) ? 0x03 : 0x00), 1);  /* 9-12 */

	/* 878's MUX0 is already selected for input via muxsel values */
}