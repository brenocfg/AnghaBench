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
struct vivid_dev {scalar_t__* output_type; size_t output; } ;

/* Variables and functions */
 scalar_t__ HDMI ; 

__attribute__((used)) static inline bool vivid_is_hdmi_out(const struct vivid_dev *dev)
{
	return dev->output_type[dev->output] == HDMI;
}