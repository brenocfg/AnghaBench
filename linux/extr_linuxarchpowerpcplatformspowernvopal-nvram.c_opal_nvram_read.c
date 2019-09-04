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
typedef  size_t ssize_t ;
typedef  scalar_t__ s64 ;
typedef  int loff_t ;

/* Variables and functions */
 size_t EIO ; 
 scalar_t__ OPAL_SUCCESS ; 
 int /*<<< orphan*/  __pa (char*) ; 
 int nvram_size ; 
 scalar_t__ opal_read_nvram (int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static ssize_t opal_nvram_read(char *buf, size_t count, loff_t *index)
{
	s64 rc;
	int off;

	if (*index >= nvram_size)
		return 0;
	off = *index;
	if ((off + count) > nvram_size)
		count = nvram_size - off;
	rc = opal_read_nvram(__pa(buf), count, off);
	if (rc != OPAL_SUCCESS)
		return -EIO;
	*index += count;
	return count;
}