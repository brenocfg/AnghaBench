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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_char (struct vc_data*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  say_attributes (struct vc_data*) ; 
 int /*<<< orphan*/  speak_char (int /*<<< orphan*/ ) ; 
 scalar_t__ spk_attr ; 
 int spk_attrib_bleep ; 
 scalar_t__ spk_old_attr ; 
 scalar_t__ spk_pos ; 
 int /*<<< orphan*/  spk_y ; 

__attribute__((used)) static void say_char(struct vc_data *vc)
{
	u16 ch;

	spk_old_attr = spk_attr;
	ch = get_char(vc, (u_short *)spk_pos, &spk_attr);
	if (spk_attr != spk_old_attr) {
		if (spk_attrib_bleep & 1)
			bleep(spk_y);
		if (spk_attrib_bleep & 2)
			say_attributes(vc);
	}
	speak_char(ch);
}