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
struct siox_device {int dummy; } ;

/* Variables and functions */
 int SIOX_STATUS_WDG ; 

__attribute__((used)) static bool siox_device_wdg_error(struct siox_device *sdevice, u8 status_clean)
{
	return (status_clean & SIOX_STATUS_WDG) == 0;
}