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

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_GPJ (int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx1950_bat_exit(void)
{
	gpio_free(S3C2410_GPJ(2));
	gpio_free(S3C2410_GPJ(3));
}