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
struct controller {int dummy; } ;

/* Variables and functions */
 int show_ctrl (struct controller*,char*) ; 
 int show_dev (struct controller*,char*) ; 

__attribute__((used)) static int spew_debug_info(struct controller *ctrl, char *data, int size)
{
	int used;

	used = size - show_ctrl(ctrl, data);
	used = (size - used) - show_dev(ctrl, &data[used]);
	return used;
}