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
typedef  int uint32_t ;
typedef  enum hdmi_acr_cts { ____Placeholder_hdmi_acr_cts } hdmi_acr_cts ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t REG_HDMI_ACR_0(enum hdmi_acr_cts i0) { return 0x000000c4 + 0x8*i0; }