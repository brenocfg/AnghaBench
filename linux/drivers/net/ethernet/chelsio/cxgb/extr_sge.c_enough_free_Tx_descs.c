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
struct cmdQ {unsigned int processed; unsigned int cleaned; unsigned int in_use; int size; } ;

/* Variables and functions */

__attribute__((used)) static inline int enough_free_Tx_descs(const struct cmdQ *q)
{
	unsigned int r = q->processed - q->cleaned;

	return q->in_use - r < (q->size >> 1);
}