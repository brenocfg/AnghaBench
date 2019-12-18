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
struct f_hid_opts {int minor; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int major ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 struct f_hid_opts* to_f_hid_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t f_hid_opts_dev_show(struct config_item *item, char *page)
{
	struct f_hid_opts *opts = to_f_hid_opts(item);

	return sprintf(page, "%d:%d\n", major, opts->minor);
}