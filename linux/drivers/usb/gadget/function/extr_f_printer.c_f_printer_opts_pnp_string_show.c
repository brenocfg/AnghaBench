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
struct f_printer_opts {int /*<<< orphan*/  lock; int /*<<< orphan*/  pnp_string; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 struct f_printer_opts* to_f_printer_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t f_printer_opts_pnp_string_show(struct config_item *item,
					      char *page)
{
	struct f_printer_opts *opts = to_f_printer_opts(item);
	int result = 0;

	mutex_lock(&opts->lock);
	if (!opts->pnp_string)
		goto unlock;

	result = strlcpy(page, opts->pnp_string, PAGE_SIZE);
	if (result >= PAGE_SIZE) {
		result = PAGE_SIZE;
	} else if (page[result - 1] != '\n' && result + 1 < PAGE_SIZE) {
		page[result++] = '\n';
		page[result] = '\0';
	}

unlock:
	mutex_unlock(&opts->lock);

	return result;
}