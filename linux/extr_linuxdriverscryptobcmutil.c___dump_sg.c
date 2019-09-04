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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  KERN_ALERT ; 
 scalar_t__ debug_logging_sleep ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 scalar_t__ packet_debug_logging ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  sg_copy_part_to_buf (struct scatterlist*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

void __dump_sg(struct scatterlist *sg, unsigned int skip, unsigned int len)
{
	u8 dbuf[16];
	unsigned int idx = skip;
	unsigned int num_out = 0;	/* number of bytes dumped so far */
	unsigned int count;

	if (packet_debug_logging) {
		while (num_out < len) {
			count = (len - num_out > 16) ? 16 : len - num_out;
			sg_copy_part_to_buf(sg, dbuf, count, idx);
			num_out += count;
			print_hex_dump(KERN_ALERT, "  sg: ", DUMP_PREFIX_NONE,
				       4, 1, dbuf, count, false);
			idx += 16;
		}
	}
	if (debug_logging_sleep)
		msleep(debug_logging_sleep);
}