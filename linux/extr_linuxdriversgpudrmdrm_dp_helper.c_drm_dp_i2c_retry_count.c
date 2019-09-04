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
struct drm_dp_aux_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUX_RETRY_INTERVAL ; 
 int DIV_ROUND_UP (int,scalar_t__) ; 
 int drm_dp_aux_reply_duration (struct drm_dp_aux_msg const*) ; 
 int drm_dp_aux_req_duration (struct drm_dp_aux_msg const*) ; 
 int drm_dp_i2c_msg_duration (struct drm_dp_aux_msg const*,int) ; 

__attribute__((used)) static int drm_dp_i2c_retry_count(const struct drm_dp_aux_msg *msg,
			      int i2c_speed_khz)
{
	int aux_time_us = drm_dp_aux_req_duration(msg) +
		drm_dp_aux_reply_duration(msg);
	int i2c_time_us = drm_dp_i2c_msg_duration(msg, i2c_speed_khz);

	return DIV_ROUND_UP(i2c_time_us, aux_time_us + AUX_RETRY_INTERVAL);
}