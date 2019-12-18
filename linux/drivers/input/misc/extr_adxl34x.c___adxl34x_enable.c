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
struct TYPE_2__ {int power_mode; } ;
struct adxl34x {TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_WRITE (struct adxl34x*,int /*<<< orphan*/ ,int) ; 
 int PCTL_MEASURE ; 
 int /*<<< orphan*/  POWER_CTL ; 

__attribute__((used)) static void __adxl34x_enable(struct adxl34x *ac)
{
	AC_WRITE(ac, POWER_CTL, ac->pdata.power_mode | PCTL_MEASURE);
}