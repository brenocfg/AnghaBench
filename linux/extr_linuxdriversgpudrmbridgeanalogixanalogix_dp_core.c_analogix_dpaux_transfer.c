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
struct drm_dp_aux {int dummy; } ;
struct analogix_dp_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  analogix_dp_transfer (struct analogix_dp_device*,struct drm_dp_aux_msg*) ; 
 struct analogix_dp_device* to_dp (struct drm_dp_aux*) ; 

__attribute__((used)) static ssize_t analogix_dpaux_transfer(struct drm_dp_aux *aux,
				       struct drm_dp_aux_msg *msg)
{
	struct analogix_dp_device *dp = to_dp(aux);

	return analogix_dp_transfer(dp, msg);
}