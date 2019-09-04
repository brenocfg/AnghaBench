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
typedef  int /*<<< orphan*/  u32 ;
struct BD_HEADER {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 

u32 spum_payload_length(u8 *spu_hdr)
{
	struct BD_HEADER *bd;
	u32 pl_len;

	/* Find BD header.  skip MH, EMH */
	bd = (struct BD_HEADER *)(spu_hdr + 8);
	pl_len = be16_to_cpu(bd->size);

	return pl_len;
}