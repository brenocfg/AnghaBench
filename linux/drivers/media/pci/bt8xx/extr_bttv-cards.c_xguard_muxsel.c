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
#define  ENA0 135 
#define  ENA1 134 
#define  ENB0 133 
#define  ENB1 132 
#define  IN00 131 
#define  IN01 130 
#define  IN10 129 
#define  IN11 128 
 int /*<<< orphan*/  gpio_write (int const) ; 

__attribute__((used)) static void xguard_muxsel(struct bttv *btv, unsigned int input)
{
	static const int masks[] = {
		ENB0, ENB0|IN00, ENB0|IN10, ENB0|IN00|IN10,
		ENA0, ENA0|IN00, ENA0|IN10, ENA0|IN00|IN10,
		ENB1, ENB1|IN01, ENB1|IN11, ENB1|IN01|IN11,
		ENA1, ENA1|IN01, ENA1|IN11, ENA1|IN01|IN11,
	};
	gpio_write(masks[input%16]);
}