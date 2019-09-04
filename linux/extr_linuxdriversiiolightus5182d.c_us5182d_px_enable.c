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
typedef  int /*<<< orphan*/  u8 ;
struct us5182d_data {scalar_t__ power_mode; int als_enabled; int px_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  US5182D_ALS_PX ; 
 scalar_t__ US5182D_ONESHOT ; 
 int /*<<< orphan*/  US5182D_PX_ONLY ; 
 int us5182d_set_opmode (struct us5182d_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int us5182d_px_enable(struct us5182d_data *data)
{
	int ret;
	u8 mode;

	if (data->power_mode == US5182D_ONESHOT) {
		ret = us5182d_set_opmode(data, US5182D_PX_ONLY);
		if (ret < 0)
			return ret;
		data->als_enabled = false;
	}

	if (data->px_enabled)
		return 0;

	mode = data->als_enabled ? US5182D_ALS_PX : US5182D_PX_ONLY;

	ret = us5182d_set_opmode(data, mode);
	if (ret < 0)
		return ret;

	data->px_enabled = true;

	return 0;
}