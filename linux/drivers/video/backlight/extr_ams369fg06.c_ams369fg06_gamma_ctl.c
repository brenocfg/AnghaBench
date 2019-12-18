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
struct ams369fg06 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * gamma_22_table; } ;

/* Variables and functions */
 int _ams369fg06_gamma_ctl (struct ams369fg06*,int /*<<< orphan*/ ) ; 
 TYPE_1__ gamma_table ; 

__attribute__((used)) static int ams369fg06_gamma_ctl(struct ams369fg06 *lcd, int brightness)
{
	int ret = 0;
	int gamma = 0;

	if ((brightness >= 0) && (brightness <= 50))
		gamma = 0;
	else if ((brightness > 50) && (brightness <= 100))
		gamma = 1;
	else if ((brightness > 100) && (brightness <= 150))
		gamma = 2;
	else if ((brightness > 150) && (brightness <= 200))
		gamma = 3;
	else if ((brightness > 200) && (brightness <= 255))
		gamma = 4;

	ret = _ams369fg06_gamma_ctl(lcd, gamma_table.gamma_22_table[gamma]);

	return ret;
}