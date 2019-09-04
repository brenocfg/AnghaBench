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
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (scalar_t__,scalar_t__) ; 
 scalar_t__ motor_off_timer ; 

__attribute__((used)) static void floppy_off (unsigned int nr)
{
	int drive;

	drive = nr & 3;
	mod_timer(motor_off_timer + drive, jiffies + 3*HZ);
}