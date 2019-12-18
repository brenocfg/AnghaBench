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
struct ib_umad_file {int use_pkey_index; int /*<<< orphan*/  mutex; scalar_t__ already_used; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long ib_umad_enable_pkey(struct ib_umad_file *file)
{
	int ret = 0;

	mutex_lock(&file->mutex);
	if (file->already_used)
		ret = -EINVAL;
	else
		file->use_pkey_index = 1;
	mutex_unlock(&file->mutex);

	return ret;
}