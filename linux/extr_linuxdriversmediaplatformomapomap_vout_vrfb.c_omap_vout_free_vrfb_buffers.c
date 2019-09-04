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
struct omap_vout_device {scalar_t__* smsshado_phy_addr; scalar_t__* smsshado_virt_addr; int /*<<< orphan*/  smsshado_size; } ;

/* Variables and functions */
 int VRFB_NUM_BUFS ; 
 int /*<<< orphan*/  omap_vout_free_buffer (scalar_t__,int /*<<< orphan*/ ) ; 

void omap_vout_free_vrfb_buffers(struct omap_vout_device *vout)
{
	int j;

	for (j = 0; j < VRFB_NUM_BUFS; j++) {
		if (vout->smsshado_virt_addr[j]) {
			omap_vout_free_buffer(vout->smsshado_virt_addr[j],
					      vout->smsshado_size);
			vout->smsshado_virt_addr[j] = 0;
			vout->smsshado_phy_addr[j] = 0;
		}
	}
}