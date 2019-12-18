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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 void* recv_buffer_fast_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *octeon_fast_packet_alloc(u32 size)
{
	return recv_buffer_fast_alloc(size);
}