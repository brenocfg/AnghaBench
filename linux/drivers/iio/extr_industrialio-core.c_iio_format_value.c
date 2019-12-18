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
typedef  int ssize_t ;

/* Variables and functions */
 int EFBIG ; 
 int PAGE_SIZE ; 
 int __iio_format_value (char*,int,unsigned int,int,int*) ; 
 int sprintf (char*,char*) ; 

ssize_t iio_format_value(char *buf, unsigned int type, int size, int *vals)
{
	ssize_t len;

	len = __iio_format_value(buf, PAGE_SIZE, type, size, vals);
	if (len >= PAGE_SIZE - 1)
		return -EFBIG;

	return len + sprintf(buf + len, "\n");
}