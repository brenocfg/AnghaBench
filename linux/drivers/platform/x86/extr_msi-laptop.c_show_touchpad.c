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
typedef  int u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_STANDARD_EC_FUNCTIONS_ADDRESS ; 
 int MSI_STANDARD_EC_TOUCHPAD_MASK ; 
 int ec_read (int /*<<< orphan*/ ,int*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_touchpad(struct device *dev,
	struct device_attribute *attr, char *buf)
{

	u8 rdata;
	int result;

	result = ec_read(MSI_STANDARD_EC_FUNCTIONS_ADDRESS, &rdata);
	if (result < 0)
		return result;

	return sprintf(buf, "%i\n", !!(rdata & MSI_STANDARD_EC_TOUCHPAD_MASK));
}