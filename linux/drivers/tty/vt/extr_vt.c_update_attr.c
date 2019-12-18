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
struct vc_data {int vc_attr; int vc_intensity; int vc_reverse; int vc_decscnm; int vc_video_erase_char; int /*<<< orphan*/  vc_blink; int /*<<< orphan*/  vc_color; int /*<<< orphan*/  vc_italic; int /*<<< orphan*/  vc_underline; } ;

/* Variables and functions */
 int build_attr (struct vc_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_attr(struct vc_data *vc)
{
	vc->vc_attr = build_attr(vc, vc->vc_color, vc->vc_intensity,
	              vc->vc_blink, vc->vc_underline,
	              vc->vc_reverse ^ vc->vc_decscnm, vc->vc_italic);
	vc->vc_video_erase_char = (build_attr(vc, vc->vc_color, 1, vc->vc_blink, 0, vc->vc_decscnm, 0) << 8) | ' ';
}