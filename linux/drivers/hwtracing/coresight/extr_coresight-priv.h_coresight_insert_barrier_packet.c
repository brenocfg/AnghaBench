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
 int /*<<< orphan*/  CORESIGHT_BARRIER_PKT_SIZE ; 
 int /*<<< orphan*/  barrier_pkt ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void coresight_insert_barrier_packet(void *buf)
{
	if (buf)
		memcpy(buf, barrier_pkt, CORESIGHT_BARRIER_PKT_SIZE);
}