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
typedef  int /*<<< orphan*/  dbf ;

/* Variables and functions */
 int /*<<< orphan*/  CHSC_LOG (int /*<<< orphan*/ ,char*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * on_close_chsc_area ; 
 int /*<<< orphan*/  on_close_mutex ; 
 int /*<<< orphan*/ * on_close_request ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int chsc_ioctl_on_close_remove(void)
{
	char dbf[13];
	int ret;

	mutex_lock(&on_close_mutex);
	if (!on_close_chsc_area) {
		ret = -ENOENT;
		goto out_unlock;
	}
	free_page((unsigned long)on_close_chsc_area);
	on_close_chsc_area = NULL;
	kfree(on_close_request);
	on_close_request = NULL;
	ret = 0;
out_unlock:
	mutex_unlock(&on_close_mutex);
	snprintf(dbf, sizeof(dbf), "ocrret:%d", ret);
	CHSC_LOG(0, dbf);
	return ret;
}