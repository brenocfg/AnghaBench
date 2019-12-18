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
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MNP_TABLE_SIZE ; 
 int __g450_setclk (struct matrox_fb_info*,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 unsigned int* kmalloc (int,int /*<<< orphan*/ ) ; 

int matroxfb_g450_setclk(struct matrox_fb_info *minfo, unsigned int fout,
			 unsigned int pll)
{
	unsigned int* arr;
	
	arr = kmalloc(sizeof(*arr) * MNP_TABLE_SIZE * 2, GFP_KERNEL);
	if (arr) {
		int r;

		r = __g450_setclk(minfo, fout, pll, arr, arr + MNP_TABLE_SIZE);
		kfree(arr);
		return r;
	}
	return -ENOMEM;
}