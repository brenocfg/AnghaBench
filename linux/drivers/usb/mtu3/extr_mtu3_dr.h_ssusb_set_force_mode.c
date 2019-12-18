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
struct ssusb_mtk {int dummy; } ;
typedef  enum mtu3_dr_force_mode { ____Placeholder_mtu3_dr_force_mode } mtu3_dr_force_mode ;

/* Variables and functions */

__attribute__((used)) static inline void
ssusb_set_force_mode(struct ssusb_mtk *ssusb, enum mtu3_dr_force_mode mode)
{}