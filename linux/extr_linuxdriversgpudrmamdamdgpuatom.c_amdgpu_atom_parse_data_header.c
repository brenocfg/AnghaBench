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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u16 ;
struct atom_context {int data_table; int bios; } ;

/* Variables and functions */
 void* CU16 (int) ; 
 int /*<<< orphan*/  CU8 (int) ; 

bool amdgpu_atom_parse_data_header(struct atom_context *ctx, int index,
			    uint16_t * size, uint8_t * frev, uint8_t * crev,
			    uint16_t * data_start)
{
	int offset = index * 2 + 4;
	int idx = CU16(ctx->data_table + offset);
	u16 *mdt = (u16 *)(ctx->bios + ctx->data_table + 4);

	if (!mdt[index])
		return false;

	if (size)
		*size = CU16(idx);
	if (frev)
		*frev = CU8(idx + 2);
	if (crev)
		*crev = CU8(idx + 3);
	*data_start = idx;
	return true;
}