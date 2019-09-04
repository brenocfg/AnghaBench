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

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
#define  BLKIF_OP_DISCARD 132 
#define  BLKIF_OP_FLUSH_DISKCACHE 131 
#define  BLKIF_OP_READ 130 
#define  BLKIF_OP_WRITE 129 
#define  BLKIF_OP_WRITE_BARRIER 128 

__attribute__((used)) static const char *op_name(int op)
{
	static const char *const names[] = {
		[BLKIF_OP_READ] = "read",
		[BLKIF_OP_WRITE] = "write",
		[BLKIF_OP_WRITE_BARRIER] = "barrier",
		[BLKIF_OP_FLUSH_DISKCACHE] = "flush",
		[BLKIF_OP_DISCARD] = "discard" };

	if (op < 0 || op >= ARRAY_SIZE(names))
		return "unknown";

	if (!names[op])
		return "reserved";

	return names[op];
}