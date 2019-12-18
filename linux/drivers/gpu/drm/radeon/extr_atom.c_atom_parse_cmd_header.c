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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u16 ;
struct atom_context {scalar_t__ cmd_table; scalar_t__ bios; } ;

/* Variables and functions */
 int CU16 (scalar_t__) ; 
 int /*<<< orphan*/  CU8 (int) ; 

bool atom_parse_cmd_header(struct atom_context *ctx, int index, uint8_t * frev,
			   uint8_t * crev)
{
	int offset = index * 2 + 4;
	int idx = CU16(ctx->cmd_table + offset);
	u16 *mct = (u16 *)(ctx->bios + ctx->cmd_table + 4);

	if (!mct[index])
		return false;

	if (frev)
		*frev = CU8(idx + 2);
	if (crev)
		*crev = CU8(idx + 3);
	return true;
}