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
typedef  scalar_t__ u16 ;
struct dpaa_buffer_layout {scalar_t__ priv_data_size; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 scalar_t__ DPAA_FD_DATA_ALIGNMENT ; 
 scalar_t__ DPAA_HASH_RESULTS_SIZE ; 
 scalar_t__ DPAA_PARSE_RESULTS_SIZE ; 
 scalar_t__ DPAA_TIME_STAMP_SIZE ; 

__attribute__((used)) static inline u16 dpaa_get_headroom(struct dpaa_buffer_layout *bl)
{
	u16 headroom;

	/* The frame headroom must accommodate:
	 * - the driver private data area
	 * - parse results, hash results, timestamp if selected
	 * If either hash results or time stamp are selected, both will
	 * be copied to/from the frame headroom, as TS is located between PR and
	 * HR in the IC and IC copy size has a granularity of 16bytes
	 * (see description of FMBM_RICP and FMBM_TICP registers in DPAARM)
	 *
	 * Also make sure the headroom is a multiple of data_align bytes
	 */
	headroom = (u16)(bl->priv_data_size + DPAA_PARSE_RESULTS_SIZE +
		DPAA_TIME_STAMP_SIZE + DPAA_HASH_RESULTS_SIZE);

	return DPAA_FD_DATA_ALIGNMENT ? ALIGN(headroom,
					      DPAA_FD_DATA_ALIGNMENT) :
					headroom;
}