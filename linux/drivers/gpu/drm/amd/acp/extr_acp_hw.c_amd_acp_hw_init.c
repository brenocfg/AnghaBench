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
struct cgs_device {int dummy; } ;

/* Variables and functions */
 unsigned int ACP_MODE_I2S ; 
 int ENODEV ; 
 unsigned int cgs_read_register (struct cgs_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmACP_AZALIA_I2S_SELECT ; 

int amd_acp_hw_init(struct cgs_device *cgs_device,
		    unsigned acp_version_major, unsigned acp_version_minor)
{
	unsigned int acp_mode = ACP_MODE_I2S;

	if ((acp_version_major == 2) && (acp_version_minor == 2))
		acp_mode = cgs_read_register(cgs_device,
					mmACP_AZALIA_I2S_SELECT);

	if (acp_mode != ACP_MODE_I2S)
		return -ENODEV;

	return 0;
}