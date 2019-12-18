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
struct TYPE_2__ {scalar_t__ reset; } ;
struct arizona {int type; TYPE_1__ pdata; } ;

/* Variables and functions */
#define  WM5110 129 
#define  WM8280 128 
 int /*<<< orphan*/  gpiod_set_raw_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void arizona_disable_reset(struct arizona *arizona)
{
	if (arizona->pdata.reset) {
		switch (arizona->type) {
		case WM5110:
		case WM8280:
			/* Meet requirements for minimum reset duration */
			usleep_range(5000, 10000);
			break;
		default:
			break;
		}

		gpiod_set_raw_value_cansleep(arizona->pdata.reset, 1);
		usleep_range(1000, 5000);
	}
}