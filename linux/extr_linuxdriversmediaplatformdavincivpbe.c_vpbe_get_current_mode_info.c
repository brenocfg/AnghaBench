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
struct vpbe_enc_mode_info {int dummy; } ;
struct vpbe_device {struct vpbe_enc_mode_info current_timings; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int vpbe_get_current_mode_info(struct vpbe_device *vpbe_dev,
				      struct vpbe_enc_mode_info *mode_info)
{
	if (!mode_info)
		return -EINVAL;

	*mode_info = vpbe_dev->current_timings;

	return 0;
}