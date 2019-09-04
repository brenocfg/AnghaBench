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
 int /*<<< orphan*/  IRIS_GIO_OUTPUT ; 
 int /*<<< orphan*/  IRIS_GIO_PULSE ; 
 int /*<<< orphan*/  IRIS_GIO_REST ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iris_power_off(void)
{
	outb(IRIS_GIO_PULSE, IRIS_GIO_OUTPUT);
	msleep(850);
	outb(IRIS_GIO_REST, IRIS_GIO_OUTPUT);
}