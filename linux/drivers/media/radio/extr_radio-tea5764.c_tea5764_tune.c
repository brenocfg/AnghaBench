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
struct tea5764_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWARN (char*) ; 
 scalar_t__ tea5764_i2c_write (struct tea5764_device*) ; 
 int /*<<< orphan*/  tea5764_set_freq (struct tea5764_device*,int) ; 

__attribute__((used)) static void tea5764_tune(struct tea5764_device *radio, int freq)
{
	tea5764_set_freq(radio, freq);
	if (tea5764_i2c_write(radio))
		PWARN("Could not set frequency!");
}