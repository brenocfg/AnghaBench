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
struct sdma_desc {int* qw; } ;

/* Variables and functions */
 int SDMA_DESC1_GENERATION_SHIFT ; 
 int SDMA_DESC1_GENERATION_SMASK ; 

__attribute__((used)) static inline int sdma_mapping_type(struct sdma_desc *d)
{
	return (d->qw[1] & SDMA_DESC1_GENERATION_SMASK)
		>> SDMA_DESC1_GENERATION_SHIFT;
}