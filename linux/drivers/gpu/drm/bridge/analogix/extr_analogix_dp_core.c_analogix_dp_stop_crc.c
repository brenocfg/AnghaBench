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
struct drm_connector {int dummy; } ;
struct analogix_dp_device {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int drm_dp_stop_crc (int /*<<< orphan*/ *) ; 
 struct analogix_dp_device* to_dp (struct drm_connector*) ; 

int analogix_dp_stop_crc(struct drm_connector *connector)
{
	struct analogix_dp_device *dp = to_dp(connector);

	return drm_dp_stop_crc(&dp->aux);
}