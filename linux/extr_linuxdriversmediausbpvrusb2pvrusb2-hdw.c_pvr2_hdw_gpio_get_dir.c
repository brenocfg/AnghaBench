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
typedef  int /*<<< orphan*/  u32 ;
struct pvr2_hdw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_GPIO_DIR ; 
 int pvr2_read_register (struct pvr2_hdw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int pvr2_hdw_gpio_get_dir(struct pvr2_hdw *hdw,u32 *dp)
{
	return pvr2_read_register(hdw,PVR2_GPIO_DIR,dp);
}