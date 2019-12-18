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
struct tape_device {int dummy; } ;
typedef  int __u64 ;

/* Variables and functions */
 int tape_std_read_block_id (struct tape_device*,int*) ; 

__attribute__((used)) static int
tape_3590_mttell(struct tape_device *device, int mt_count)
{
	__u64 block_id;
	int rc;

	rc = tape_std_read_block_id(device, &block_id);
	if (rc)
		return rc;
	return block_id >> 32;
}