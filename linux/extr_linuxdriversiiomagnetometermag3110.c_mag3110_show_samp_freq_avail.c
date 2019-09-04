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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  mag3110_samp_freq ; 
 int /*<<< orphan*/  mag3110_show_int_plus_micros (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t mag3110_show_samp_freq_avail(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return mag3110_show_int_plus_micros(buf, mag3110_samp_freq, 8);
}