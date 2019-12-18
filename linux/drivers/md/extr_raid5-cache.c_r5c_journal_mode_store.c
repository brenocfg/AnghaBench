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
struct mddev {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int mddev_lock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 int r5c_journal_mode_set (struct mddev*,int) ; 
 int /*<<< orphan*/ * r5c_journal_mode_str ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ssize_t r5c_journal_mode_store(struct mddev *mddev,
				      const char *page, size_t length)
{
	int mode = ARRAY_SIZE(r5c_journal_mode_str);
	size_t len = length;
	int ret;

	if (len < 2)
		return -EINVAL;

	if (page[len - 1] == '\n')
		len--;

	while (mode--)
		if (strlen(r5c_journal_mode_str[mode]) == len &&
		    !strncmp(page, r5c_journal_mode_str[mode], len))
			break;
	ret = mddev_lock(mddev);
	if (ret)
		return ret;
	ret = r5c_journal_mode_set(mddev, mode);
	mddev_unlock(mddev);
	return ret ?: length;
}