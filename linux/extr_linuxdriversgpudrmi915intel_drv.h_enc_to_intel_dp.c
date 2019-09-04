#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_dp {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {struct intel_dp dp; } ;

/* Variables and functions */
 TYPE_1__* enc_to_dig_port (struct drm_encoder*) ; 

__attribute__((used)) static inline struct intel_dp *enc_to_intel_dp(struct drm_encoder *encoder)
{
	return &enc_to_dig_port(encoder)->dp;
}