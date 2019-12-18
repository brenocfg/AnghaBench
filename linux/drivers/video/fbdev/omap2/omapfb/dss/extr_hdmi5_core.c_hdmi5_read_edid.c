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
struct hdmi_core_data {int dummy; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int EINVAL ; 
 int hdmi_core_ddc_edid (struct hdmi_core_data*,int*,int) ; 
 int /*<<< orphan*/  hdmi_core_ddc_init (struct hdmi_core_data*) ; 
 int /*<<< orphan*/  hdmi_core_ddc_uninit (struct hdmi_core_data*) ; 

int hdmi5_read_edid(struct hdmi_core_data *core, u8 *edid, int len)
{
	int r, n, i;
	int max_ext_blocks = (len / 128) - 1;

	if (len < 128)
		return -EINVAL;

	hdmi_core_ddc_init(core);

	r = hdmi_core_ddc_edid(core, edid, 0);
	if (r)
		goto out;

	n = edid[0x7e];

	if (n > max_ext_blocks)
		n = max_ext_blocks;

	for (i = 1; i <= n; i++) {
		r = hdmi_core_ddc_edid(core, edid + i * EDID_LENGTH, i);
		if (r)
			goto out;
	}

out:
	hdmi_core_ddc_uninit(core);

	return r ? r : len;
}