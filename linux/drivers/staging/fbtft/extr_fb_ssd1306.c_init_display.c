#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* curves; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_4__* info; TYPE_2__ gamma; TYPE_1__ fbtftops; } ;
struct TYPE_7__ {int yres; } ;
struct TYPE_8__ {TYPE_3__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	if (par->gamma.curves[0] == 0) {
		mutex_lock(&par->gamma.lock);
		if (par->info->var.yres == 64)
			par->gamma.curves[0] = 0xCF;
		else
			par->gamma.curves[0] = 0x8F;
		mutex_unlock(&par->gamma.lock);
	}

	/* Set Display OFF */
	write_reg(par, 0xAE);

	/* Set Display Clock Divide Ratio/ Oscillator Frequency */
	write_reg(par, 0xD5);
	write_reg(par, 0x80);

	/* Set Multiplex Ratio */
	write_reg(par, 0xA8);
	if (par->info->var.yres == 64)
		write_reg(par, 0x3F);
	else if (par->info->var.yres == 48)
		write_reg(par, 0x2F);
	else
		write_reg(par, 0x1F);

	/* Set Display Offset */
	write_reg(par, 0xD3);
	write_reg(par, 0x0);

	/* Set Display Start Line */
	write_reg(par, 0x40 | 0x0);

	/* Charge Pump Setting */
	write_reg(par, 0x8D);
	/* A[2] = 1b, Enable charge pump during display on */
	write_reg(par, 0x14);

	/* Set Memory Addressing Mode */
	write_reg(par, 0x20);
	/* Vertical addressing mode  */
	write_reg(par, 0x01);

	/* Set Segment Re-map */
	/* column address 127 is mapped to SEG0 */
	write_reg(par, 0xA0 | 0x1);

	/* Set COM Output Scan Direction */
	/* remapped mode. Scan from COM[N-1] to COM0 */
	write_reg(par, 0xC8);

	/* Set COM Pins Hardware Configuration */
	write_reg(par, 0xDA);
	if (par->info->var.yres == 64)
		/* A[4]=1b, Alternative COM pin configuration */
		write_reg(par, 0x12);
	else if (par->info->var.yres == 48)
		/* A[4]=1b, Alternative COM pin configuration */
		write_reg(par, 0x12);
	else
		/* A[4]=0b, Sequential COM pin configuration */
		write_reg(par, 0x02);

	/* Set Pre-charge Period */
	write_reg(par, 0xD9);
	write_reg(par, 0xF1);

	/* Set VCOMH Deselect Level */
	write_reg(par, 0xDB);
	/* according to the datasheet, this value is out of bounds */
	write_reg(par, 0x40);

	/* Entire Display ON */
	/* Resume to RAM content display. Output follows RAM content */
	write_reg(par, 0xA4);

	/* Set Normal Display
	 * 0 in RAM: OFF in display panel
	 * 1 in RAM: ON in display panel
	 */
	write_reg(par, 0xA6);

	/* Set Display ON */
	write_reg(par, 0xAF);

	return 0;
}