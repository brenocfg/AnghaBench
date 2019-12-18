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
struct dma_mapping {scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static inline bool dma_mapping_used(struct dma_mapping *m)
{
	if (!m)
		return false;
	return m->size != 0;
}