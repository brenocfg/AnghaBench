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
struct console_font {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int dummycon_font_set(struct vc_data *vc, struct console_font *font,
			     unsigned int flags)
{
	return 0;
}