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
typedef  struct hmcdrv_ftp_cmdspec {scalar_t__ len; int ofs; int /*<<< orphan*/  fname; int /*<<< orphan*/  id; int /*<<< orphan*/  buf; } const hmcdrv_ftp_cmdspec ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ (* hmcdrv_cache_ftpfunc ) (struct hmcdrv_ftp_cmdspec const*,int /*<<< orphan*/ *) ;
struct TYPE_2__ {scalar_t__ len; int ofs; int /*<<< orphan*/  fsize; int /*<<< orphan*/  id; int /*<<< orphan*/  fname; int /*<<< orphan*/  content; scalar_t__ timeout; } ;

/* Variables and functions */
 int HMCDRV_CACHE_TIMEOUT ; 
 int /*<<< orphan*/  HMCDRV_FTP_FIDENT_MAX ; 
 int HZ ; 
 TYPE_1__ hmcdrv_cache_file ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t hmcdrv_cache_do(const struct hmcdrv_ftp_cmdspec *ftp,
			       hmcdrv_cache_ftpfunc func)
{
	ssize_t len;

	/* only cache content if the read/dir cache really exists
	 * (hmcdrv_cache_file.len > 0), is large enough to handle the
	 * request (hmcdrv_cache_file.len >= ftp->len) and there is a need
	 * to do so (ftp->len > 0)
	 */
	if ((ftp->len > 0) && (hmcdrv_cache_file.len >= ftp->len)) {

		/* because the cache is not located at ftp->buf, we have to
		 * assemble a new HMC drive FTP cmd specification (pointing
		 * to our cache, and using the increased size)
		 */
		struct hmcdrv_ftp_cmdspec cftp = *ftp; /* make a copy */
		cftp.buf = hmcdrv_cache_file.content;  /* and update */
		cftp.len = hmcdrv_cache_file.len;      /* buffer data */

		len = func(&cftp, &hmcdrv_cache_file.fsize); /* now do */

		if (len > 0) {
			pr_debug("caching %zd bytes content for '%s'\n",
				 len, ftp->fname);

			if (len > ftp->len)
				len = ftp->len;

			hmcdrv_cache_file.ofs = ftp->ofs;
			hmcdrv_cache_file.timeout = jiffies +
				HMCDRV_CACHE_TIMEOUT * HZ;
			memcpy(ftp->buf, hmcdrv_cache_file.content, len);
		}
	} else {
		len = func(ftp, &hmcdrv_cache_file.fsize);
		hmcdrv_cache_file.ofs = -1; /* invalidate content */
	}

	if (len > 0) {
		/* cache some file info (FTP command, file name and file
		 * size) unconditionally
		 */
		strlcpy(hmcdrv_cache_file.fname, ftp->fname,
			HMCDRV_FTP_FIDENT_MAX);
		hmcdrv_cache_file.id = ftp->id;
		pr_debug("caching cmd %d, file size %zu for '%s'\n",
			 ftp->id, hmcdrv_cache_file.fsize, ftp->fname);
	}

	return len;
}