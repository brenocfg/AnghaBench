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
struct vc_data {int vc_intensity; int /*<<< orphan*/  vc_def_color; int /*<<< orphan*/  vc_color; scalar_t__ vc_blink; scalar_t__ vc_reverse; scalar_t__ vc_underline; scalar_t__ vc_italic; } ;

/* Variables and functions */

__attribute__((used)) static void default_attr(struct vc_data *vc)
{
	vc->vc_intensity = 1;
	vc->vc_italic = 0;
	vc->vc_underline = 0;
	vc->vc_reverse = 0;
	vc->vc_blink = 0;
	vc->vc_color = vc->vc_def_color;
}