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
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBAT_DEV_HP8200 ; 
 int init_usbat (struct us_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_usbat_cd(struct us_data *us)
{
	return init_usbat(us, USBAT_DEV_HP8200);
}