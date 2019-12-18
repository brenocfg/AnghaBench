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
struct hmcdrv_ftp_cmdspec {scalar_t__ id; scalar_t__ ofs; int len; int /*<<< orphan*/  buf; int /*<<< orphan*/  fname; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ id; scalar_t__ fsize; scalar_t__ ofs; scalar_t__ len; scalar_t__ content; int /*<<< orphan*/  fname; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 TYPE_1__ hmcdrv_cache_file ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t hmcdrv_cache_get(const struct hmcdrv_ftp_cmdspec *ftp)
{
	loff_t pos; /* position in cache (signed) */
	ssize_t len;

	if ((ftp->id != hmcdrv_cache_file.id) ||
	    strcmp(hmcdrv_cache_file.fname, ftp->fname))
		return -1;

	if (ftp->ofs >= hmcdrv_cache_file.fsize) /* EOF ? */
		return 0;

	if ((hmcdrv_cache_file.ofs < 0) || /* has content? */
	    time_after(jiffies, hmcdrv_cache_file.timeout))
		return -1;

	/* there seems to be cached content - calculate the maximum number
	 * of bytes that can be returned (regarding file size and offset)
	 */
	len = hmcdrv_cache_file.fsize - ftp->ofs;

	if (len > ftp->len)
		len = ftp->len;

	/* check if the requested chunk falls into our cache (which starts
	 * at offset 'hmcdrv_cache_file.ofs' in the file of interest)
	 */
	pos = ftp->ofs - hmcdrv_cache_file.ofs;

	if ((pos >= 0) &&
	    ((pos + len) <= hmcdrv_cache_file.len)) {

		memcpy(ftp->buf,
		       hmcdrv_cache_file.content + pos,
		       len);
		pr_debug("using cached content of '%s', returning %zd/%zd bytes\n",
			 hmcdrv_cache_file.fname, len,
			 hmcdrv_cache_file.fsize);

		return len;
	}

	return -1;
}