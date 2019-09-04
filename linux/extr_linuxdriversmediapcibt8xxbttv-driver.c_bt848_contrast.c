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
struct bttv {int contrast; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_CONTRAST_LO ; 
 int /*<<< orphan*/  BT848_E_CONTROL ; 
 int /*<<< orphan*/  BT848_O_CONTROL ; 
 int /*<<< orphan*/  btaor (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bt848_contrast(struct bttv *btv, int cont)
{
	int value,hibit;

	btv->contrast = cont;

	/* 0-511 */
	value = (cont  >> 7);
	hibit = (value >> 6) & 4;
	btwrite(value & 0xff, BT848_CONTRAST_LO);
	btaor(hibit, ~4, BT848_E_CONTROL);
	btaor(hibit, ~4, BT848_O_CONTROL);
}