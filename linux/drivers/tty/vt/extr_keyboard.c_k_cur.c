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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CKMODE ; 
 int /*<<< orphan*/  applkey (struct vc_data*,char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd ; 
 int /*<<< orphan*/  vc_kbd_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void k_cur(struct vc_data *vc, unsigned char value, char up_flag)
{
	static const char cur_chars[] = "BDCA";

	if (up_flag)
		return;

	applkey(vc, cur_chars[value], vc_kbd_mode(kbd, VC_CKMODE));
}