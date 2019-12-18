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
typedef  int u32 ;
struct snvs_rtc_data {scalar_t__ offset; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ SNVS_LPCR ; 
 int SNVS_LPCR_SRTC_ENV ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int snvs_rtc_enable(struct snvs_rtc_data *data, bool enable)
{
	int timeout = 1000;
	u32 lpcr;

	regmap_update_bits(data->regmap, data->offset + SNVS_LPCR, SNVS_LPCR_SRTC_ENV,
			   enable ? SNVS_LPCR_SRTC_ENV : 0);

	while (--timeout) {
		regmap_read(data->regmap, data->offset + SNVS_LPCR, &lpcr);

		if (enable) {
			if (lpcr & SNVS_LPCR_SRTC_ENV)
				break;
		} else {
			if (!(lpcr & SNVS_LPCR_SRTC_ENV))
				break;
		}
	}

	if (!timeout)
		return -ETIMEDOUT;

	return 0;
}