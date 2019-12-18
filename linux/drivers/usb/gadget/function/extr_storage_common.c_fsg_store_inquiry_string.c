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
struct fsg_lun {char* inquiry_string; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t min (size_t,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

ssize_t fsg_store_inquiry_string(struct fsg_lun *curlun, const char *buf,
				 size_t count)
{
	const size_t len = min(count, sizeof(curlun->inquiry_string));

	if (len == 0 || buf[0] == '\n') {
		curlun->inquiry_string[0] = 0;
	} else {
		snprintf(curlun->inquiry_string,
			 sizeof(curlun->inquiry_string), "%-28s", buf);
		if (curlun->inquiry_string[len-1] == '\n')
			curlun->inquiry_string[len-1] = ' ';
	}

	return count;
}