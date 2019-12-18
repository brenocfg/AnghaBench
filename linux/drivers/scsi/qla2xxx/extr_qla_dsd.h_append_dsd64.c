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
struct dsd64 {int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static inline void append_dsd64(struct dsd64 **dsd, struct scatterlist *sg)
{
	put_unaligned_le64(sg_dma_address(sg), &(*dsd)->address);
	put_unaligned_le32(sg_dma_len(sg),     &(*dsd)->length);
	(*dsd)++;
}