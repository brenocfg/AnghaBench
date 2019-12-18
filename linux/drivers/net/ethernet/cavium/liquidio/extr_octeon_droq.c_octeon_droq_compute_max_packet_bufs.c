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
typedef  int u32 ;
struct octeon_droq {scalar_t__ max_empty_descs; scalar_t__ max_count; scalar_t__ buffer_size; } ;

/* Variables and functions */

__attribute__((used)) static void octeon_droq_compute_max_packet_bufs(struct octeon_droq *droq)
{
	u32 count = 0;

	/* max_empty_descs is the max. no. of descs that can have no buffers.
	 * If the empty desc count goes beyond this value, we cannot safely
	 * read in a 64K packet sent by Octeon
	 * (64K is max pkt size from Octeon)
	 */
	droq->max_empty_descs = 0;

	do {
		droq->max_empty_descs++;
		count += droq->buffer_size;
	} while (count < (64 * 1024));

	droq->max_empty_descs = droq->max_count - droq->max_empty_descs;
}