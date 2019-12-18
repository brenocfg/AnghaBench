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
struct scu_sgl_element {scalar_t__ address_modifier; int /*<<< orphan*/  address_lower; int /*<<< orphan*/  address_upper; int /*<<< orphan*/  length; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_sgl_element(struct scu_sgl_element *e, struct scatterlist *sg)
{
	e->length = sg_dma_len(sg);
	e->address_upper = upper_32_bits(sg_dma_address(sg));
	e->address_lower = lower_32_bits(sg_dma_address(sg));
	e->address_modifier = 0;
}