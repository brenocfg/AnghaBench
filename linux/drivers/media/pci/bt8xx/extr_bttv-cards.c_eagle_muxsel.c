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
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_ADC ; 
 int /*<<< orphan*/  BT848_ADC_C_SLEEP ; 
 int /*<<< orphan*/  BT848_CONTROL_COMP ; 
 int /*<<< orphan*/  BT848_E_CONTROL ; 
 int /*<<< orphan*/  BT848_O_CONTROL ; 
 int LM1882_SYNC_DRIVE ; 
 int /*<<< orphan*/  btand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_bits (int,int) ; 

__attribute__((used)) static void eagle_muxsel(struct bttv *btv, unsigned int input)
{
	gpio_bits(3, input & 3);

	/* composite */
	/* set chroma ADC to sleep */
	btor(BT848_ADC_C_SLEEP, BT848_ADC);
	/* set to composite video */
	btand(~BT848_CONTROL_COMP, BT848_E_CONTROL);
	btand(~BT848_CONTROL_COMP, BT848_O_CONTROL);

	/* switch sync drive off */
	gpio_bits(LM1882_SYNC_DRIVE,LM1882_SYNC_DRIVE);
}