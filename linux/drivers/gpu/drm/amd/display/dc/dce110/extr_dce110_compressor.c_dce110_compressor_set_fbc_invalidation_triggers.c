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
typedef  int /*<<< orphan*/  uint32_t ;
struct compressor {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBC_CLIENT_REGION_MASK ; 
 int /*<<< orphan*/  FBC_IDLE_FORCE_CLEAR_MASK ; 
 int /*<<< orphan*/  FBC_MEMORY_REGION_MASK ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmFBC_CLIENT_REGION_MASK ; 
 int /*<<< orphan*/  mmFBC_IDLE_FORCE_CLEAR_MASK ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_compressor_set_fbc_invalidation_triggers(
	struct compressor *compressor,
	uint32_t fbc_trigger)
{
	/* Disable region hit event, FBC_MEMORY_REGION_MASK = 0 (bits 16-19)
	 * for DCE 11 regions cannot be used - does not work with S/G
	 */
	uint32_t addr = mmFBC_CLIENT_REGION_MASK;
	uint32_t value = dm_read_reg(compressor->ctx, addr);

	set_reg_field_value(
		value,
		0,
		FBC_CLIENT_REGION_MASK,
		FBC_MEMORY_REGION_MASK);
	dm_write_reg(compressor->ctx, addr, value);

	/* Setup events when to clear all CSM entries (effectively marking
	 * current compressed data invalid)
	 * For DCE 11 CSM metadata 11111 means - "Not Compressed"
	 * Used as the initial value of the metadata sent to the compressor
	 * after invalidation, to indicate that the compressor should attempt
	 * to compress all chunks on the current pass.  Also used when the chunk
	 * is not successfully written to memory.
	 * When this CSM value is detected, FBC reads from the uncompressed
	 * buffer. Set events according to passed in value, these events are
	 * valid for DCE11:
	 *     - bit  0 - display register updated
	 *     - bit 28 - memory write from any client except from MCIF
	 *     - bit 29 - CG static screen signal is inactive
	 * In addition, DCE11.1 also needs to set new DCE11.1 specific events
	 * that are used to trigger invalidation on certain register changes,
	 * for example enabling of Alpha Compression may trigger invalidation of
	 * FBC once bit is set. These events are as follows:
	 *      - Bit 2 - FBC_GRPH_COMP_EN register updated
	 *      - Bit 3 - FBC_SRC_SEL register updated
	 *      - Bit 4 - FBC_MIN_COMPRESSION register updated
	 *      - Bit 5 - FBC_ALPHA_COMP_EN register updated
	 *      - Bit 6 - FBC_ZERO_ALPHA_CHUNK_SKIP_EN register updated
	 *      - Bit 7 - FBC_FORCE_COPY_TO_COMP_BUF register updated
	 */
	addr = mmFBC_IDLE_FORCE_CLEAR_MASK;
	value = dm_read_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		fbc_trigger,
		FBC_IDLE_FORCE_CLEAR_MASK,
		FBC_IDLE_FORCE_CLEAR_MASK);
	dm_write_reg(compressor->ctx, addr, value);
}