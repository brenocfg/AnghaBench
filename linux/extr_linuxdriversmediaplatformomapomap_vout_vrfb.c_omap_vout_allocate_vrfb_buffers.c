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
struct omap_vout_device {scalar_t__ memory; int /*<<< orphan*/  smsshado_size; scalar_t__* smsshado_virt_addr; scalar_t__* smsshado_phy_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omap_vout_alloc_buffer (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  omap_vout_free_buffer (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_vout_allocate_vrfb_buffers(struct omap_vout_device *vout,
		unsigned int *count, int startindex)
{
	int i, j;

	for (i = 0; i < *count; i++) {
		if (!vout->smsshado_virt_addr[i]) {
			vout->smsshado_virt_addr[i] =
				omap_vout_alloc_buffer(vout->smsshado_size,
						&vout->smsshado_phy_addr[i]);
		}
		if (!vout->smsshado_virt_addr[i] && startindex != -1) {
			if (V4L2_MEMORY_MMAP == vout->memory && i >= startindex)
				break;
		}
		if (!vout->smsshado_virt_addr[i]) {
			for (j = 0; j < i; j++) {
				omap_vout_free_buffer(
						vout->smsshado_virt_addr[j],
						vout->smsshado_size);
				vout->smsshado_virt_addr[j] = 0;
				vout->smsshado_phy_addr[j] = 0;
			}
			*count = 0;
			return -ENOMEM;
		}
		memset((void *)(long)vout->smsshado_virt_addr[i], 0,
		       vout->smsshado_size);
	}
	return 0;
}