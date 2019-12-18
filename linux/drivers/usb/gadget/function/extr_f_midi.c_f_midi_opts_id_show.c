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
struct f_midi_opts {int /*<<< orphan*/  lock; scalar_t__ id; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlcpy (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct f_midi_opts* to_f_midi_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t f_midi_opts_id_show(struct config_item *item, char *page)
{
	struct f_midi_opts *opts = to_f_midi_opts(item);
	int result;

	mutex_lock(&opts->lock);
	if (opts->id) {
		result = strlcpy(page, opts->id, PAGE_SIZE);
	} else {
		page[0] = 0;
		result = 0;
	}

	mutex_unlock(&opts->lock);

	return result;
}