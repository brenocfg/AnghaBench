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
struct console {int dummy; } ;

/* Variables and functions */
 scalar_t__ pti_console_channel ; 
 scalar_t__ pti_control_channel ; 

__attribute__((used)) static int pti_console_setup(struct console *c, char *opts)
{
	pti_console_channel = 0;
	pti_control_channel = 0;
	return 0;
}