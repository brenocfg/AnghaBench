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
typedef  size_t u32 ;
struct bttv {int dummy; } ;

/* Variables and functions */
 int BTTV_ALT_DATA ; 
 int BTTV_ALT_DCLK ; 
 int BTTV_ALT_NCONFIG ; 
 int /*<<< orphan*/  PVR_GPIO_DELAY ; 
 int /*<<< orphan*/  gpio_bits (int,int) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 
 int /*<<< orphan*/  gpio_write (int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr_altera_load(struct bttv *btv, const u8 *micro, u32 microlen)
{
	u32 n;
	u8 bits;
	int i;

	gpio_inout(0xffffff,BTTV_ALT_DATA|BTTV_ALT_DCLK|BTTV_ALT_NCONFIG);
	gpio_write(0);
	udelay(PVR_GPIO_DELAY);

	gpio_write(BTTV_ALT_NCONFIG);
	udelay(PVR_GPIO_DELAY);

	for (n = 0; n < microlen; n++) {
		bits = micro[n];
		for (i = 0 ; i < 8 ; i++) {
			gpio_bits(BTTV_ALT_DCLK,0);
			if (bits & 0x01)
				gpio_bits(BTTV_ALT_DATA,BTTV_ALT_DATA);
			else
				gpio_bits(BTTV_ALT_DATA,0);
			gpio_bits(BTTV_ALT_DCLK,BTTV_ALT_DCLK);
			bits >>= 1;
		}
	}
	gpio_bits(BTTV_ALT_DCLK,0);
	udelay(PVR_GPIO_DELAY);

	/* begin Altera init loop (Not necessary,but doesn't hurt) */
	for (i = 0 ; i < 30 ; i++) {
		gpio_bits(BTTV_ALT_DCLK,0);
		gpio_bits(BTTV_ALT_DCLK,BTTV_ALT_DCLK);
	}
	gpio_bits(BTTV_ALT_DCLK,0);
	return 0;
}