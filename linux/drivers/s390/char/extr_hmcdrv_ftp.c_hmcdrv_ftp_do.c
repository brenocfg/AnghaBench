#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hmcdrv_ftp_cmdspec {int /*<<< orphan*/  len; scalar_t__ ofs; int /*<<< orphan*/  fname; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  transfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  hmcdrv_cache_cmd (struct hmcdrv_ftp_cmdspec const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* hmcdrv_ftp_funcs ; 
 int /*<<< orphan*/  hmcdrv_ftp_mutex ; 
 scalar_t__ hmcdrv_ftp_refcnt ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ) ; 

ssize_t hmcdrv_ftp_do(const struct hmcdrv_ftp_cmdspec *ftp)
{
	ssize_t len;

	mutex_lock(&hmcdrv_ftp_mutex);

	if (hmcdrv_ftp_funcs && hmcdrv_ftp_refcnt) {
		pr_debug("starting transfer, cmd %d for '%s' at %lld with %zd bytes\n",
			 ftp->id, ftp->fname, (long long) ftp->ofs, ftp->len);
		len = hmcdrv_cache_cmd(ftp, hmcdrv_ftp_funcs->transfer);
	} else {
		len = -ENXIO;
	}

	mutex_unlock(&hmcdrv_ftp_mutex);
	return len;
}