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
typedef  int u16 ;
struct wm8350 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8350_GP0_FN_MASK ; 
 int WM8350_GP10_FN_MASK ; 
 int WM8350_GP11_FN_MASK ; 
 int WM8350_GP12_FN_MASK ; 
 int WM8350_GP1_FN_MASK ; 
 int WM8350_GP2_FN_MASK ; 
 int WM8350_GP3_FN_MASK ; 
 int WM8350_GP4_FN_MASK ; 
 int WM8350_GP5_FN_MASK ; 
 int WM8350_GP6_FN_MASK ; 
 int WM8350_GP7_FN_MASK ; 
 int WM8350_GP8_FN_MASK ; 
 int WM8350_GP9_FN_MASK ; 
 int /*<<< orphan*/  WM8350_GPIO_FUNCTION_SELECT_1 ; 
 int /*<<< orphan*/  WM8350_GPIO_FUNCTION_SELECT_2 ; 
 int /*<<< orphan*/  WM8350_GPIO_FUNCTION_SELECT_3 ; 
 int /*<<< orphan*/  WM8350_GPIO_FUNCTION_SELECT_4 ; 
 int /*<<< orphan*/  wm8350_reg_lock (struct wm8350*) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_reg_unlock (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gpio_set_func(struct wm8350 *wm8350, int gpio, int func)
{
	u16 reg;

	wm8350_reg_unlock(wm8350);
	switch (gpio) {
	case 0:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_1)
		    & ~WM8350_GP0_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_1,
				 reg | ((func & 0xf) << 0));
		break;
	case 1:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_1)
		    & ~WM8350_GP1_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_1,
				 reg | ((func & 0xf) << 4));
		break;
	case 2:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_1)
		    & ~WM8350_GP2_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_1,
				 reg | ((func & 0xf) << 8));
		break;
	case 3:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_1)
		    & ~WM8350_GP3_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_1,
				 reg | ((func & 0xf) << 12));
		break;
	case 4:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_2)
		    & ~WM8350_GP4_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_2,
				 reg | ((func & 0xf) << 0));
		break;
	case 5:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_2)
		    & ~WM8350_GP5_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_2,
				 reg | ((func & 0xf) << 4));
		break;
	case 6:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_2)
		    & ~WM8350_GP6_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_2,
				 reg | ((func & 0xf) << 8));
		break;
	case 7:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_2)
		    & ~WM8350_GP7_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_2,
				 reg | ((func & 0xf) << 12));
		break;
	case 8:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_3)
		    & ~WM8350_GP8_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_3,
				 reg | ((func & 0xf) << 0));
		break;
	case 9:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_3)
		    & ~WM8350_GP9_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_3,
				 reg | ((func & 0xf) << 4));
		break;
	case 10:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_3)
		    & ~WM8350_GP10_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_3,
				 reg | ((func & 0xf) << 8));
		break;
	case 11:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_3)
		    & ~WM8350_GP11_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_3,
				 reg | ((func & 0xf) << 12));
		break;
	case 12:
		reg = wm8350_reg_read(wm8350, WM8350_GPIO_FUNCTION_SELECT_4)
		    & ~WM8350_GP12_FN_MASK;
		wm8350_reg_write(wm8350, WM8350_GPIO_FUNCTION_SELECT_4,
				 reg | ((func & 0xf) << 0));
		break;
	default:
		wm8350_reg_lock(wm8350);
		return -EINVAL;
	}

	wm8350_reg_lock(wm8350);
	return 0;
}