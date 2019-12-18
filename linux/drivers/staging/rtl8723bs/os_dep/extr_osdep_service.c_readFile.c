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
struct file {int /*<<< orphan*/  f_pos; TYPE_1__* f_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  read; } ;

/* Variables and functions */
 int EPERM ; 
 int kernel_read (struct file*,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int readFile(struct file *fp, char *buf, int len)
{
	int rlen = 0, sum = 0;

	if (!fp->f_op || !fp->f_op->read)
		return -EPERM;

	while (sum < len) {
		rlen = kernel_read(fp, buf + sum, len - sum, &fp->f_pos);
		if (rlen > 0)
			sum += rlen;
		else if (0 != rlen)
			return rlen;
		else
			break;
	}

	return sum;

}