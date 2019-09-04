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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t devcd_readv(char *buffer, loff_t offset, size_t count,
			   void *data, size_t datalen)
{
	if (offset > datalen)
		return -EINVAL;

	if (offset + count > datalen)
		count = datalen - offset;

	if (count)
		memcpy(buffer, ((u8 *)data) + offset, count);

	return count;
}