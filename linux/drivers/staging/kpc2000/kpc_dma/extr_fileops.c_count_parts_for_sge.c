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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static inline
unsigned int  count_parts_for_sge(struct scatterlist *sg)
{
	return DIV_ROUND_UP(sg_dma_len(sg), 0x80000);
}