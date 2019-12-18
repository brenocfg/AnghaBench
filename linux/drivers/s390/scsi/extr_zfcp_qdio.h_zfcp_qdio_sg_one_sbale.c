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
 scalar_t__ ZFCP_QDIO_SBALE_LEN ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 

__attribute__((used)) static inline
int zfcp_qdio_sg_one_sbale(struct scatterlist *sg)
{
	return sg_is_last(sg) && sg->length <= ZFCP_QDIO_SBALE_LEN;
}