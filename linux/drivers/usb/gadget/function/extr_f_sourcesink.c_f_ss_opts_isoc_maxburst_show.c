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
struct f_ss_opts {int isoc_maxburst; int /*<<< orphan*/  lock; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 struct f_ss_opts* to_f_ss_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t f_ss_opts_isoc_maxburst_show(struct config_item *item, char *page)
{
	struct f_ss_opts *opts = to_f_ss_opts(item);
	int result;

	mutex_lock(&opts->lock);
	result = sprintf(page, "%u\n", opts->isoc_maxburst);
	mutex_unlock(&opts->lock);

	return result;
}