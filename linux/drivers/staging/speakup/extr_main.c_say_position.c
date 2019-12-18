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
struct vc_data {scalar_t__ vc_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_POS_INFO ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 scalar_t__ spk_x ; 
 scalar_t__ spk_y ; 
 int /*<<< orphan*/  synth_printf (char*,...) ; 

__attribute__((used)) static void say_position(struct vc_data *vc)
{
	synth_printf(spk_msg_get(MSG_POS_INFO), spk_y + 1, spk_x + 1,
		     vc->vc_num + 1);
	synth_printf("\n");
}