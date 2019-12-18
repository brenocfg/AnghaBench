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
struct scatterlist {scalar_t__ length; } ;

/* Variables and functions */
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static inline
unsigned int zfcp_qdio_real_bytes(struct scatterlist *sg)
{
	unsigned int real_bytes = 0;

	for (; sg; sg = sg_next(sg))
		real_bytes += sg->length;

	return real_bytes;
}