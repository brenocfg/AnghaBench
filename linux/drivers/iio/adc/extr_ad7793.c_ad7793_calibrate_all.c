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
struct ad7793_state {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad7793_calib_arr ; 
 int ad_sd_calibrate_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7793_calibrate_all(struct ad7793_state *st)
{
	return ad_sd_calibrate_all(&st->sd, ad7793_calib_arr,
				   ARRAY_SIZE(ad7793_calib_arr));
}