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
struct file {struct cs_char* private_data; } ;
struct cs_char {int /*<<< orphan*/  async_queue; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs_char_fasync(int fd, struct file *file, int on)
{
	struct cs_char *csdata = file->private_data;

	if (fasync_helper(fd, file, on, &csdata->async_queue) < 0)
		return -EIO;

	return 0;
}