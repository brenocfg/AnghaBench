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
typedef  scalar_t__ u64 ;
struct scatterlist {scalar_t__ length; } ;

/* Variables and functions */
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static u64 virtio_crypto_alg_sg_nents_length(struct scatterlist *sg)
{
	u64 total = 0;

	for (total = 0; sg; sg = sg_next(sg))
		total += sg->length;

	return total;
}