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
struct tmc_drvdata {struct etr_buf* sysfs_buf; } ;
struct etr_buf {scalar_t__ len; scalar_t__ offset; scalar_t__ size; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ tmc_etr_buf_get_data (struct etr_buf*,scalar_t__,scalar_t__,char**) ; 

ssize_t tmc_etr_get_sysfs_trace(struct tmc_drvdata *drvdata,
				loff_t pos, size_t len, char **bufpp)
{
	s64 offset;
	ssize_t actual = len;
	struct etr_buf *etr_buf = drvdata->sysfs_buf;

	if (pos + actual > etr_buf->len)
		actual = etr_buf->len - pos;
	if (actual <= 0)
		return actual;

	/* Compute the offset from which we read the data */
	offset = etr_buf->offset + pos;
	if (offset >= etr_buf->size)
		offset -= etr_buf->size;
	return tmc_etr_buf_get_data(etr_buf, offset, actual, bufpp);
}