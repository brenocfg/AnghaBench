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
 unsigned int ARRAY_SIZE (char const**) ; 
 char const** fcpio_status_str ; 

__attribute__((used)) static const char *fnic_fcpio_status_to_str(unsigned int status)
{
	if (status >= ARRAY_SIZE(fcpio_status_str) || !fcpio_status_str[status])
		return "unknown";

	return fcpio_status_str[status];
}