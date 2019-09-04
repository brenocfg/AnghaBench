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
struct ccp_dm_workarea {scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (scalar_t__,struct scatterlist*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void ccp_get_dm_area(struct ccp_dm_workarea *wa, unsigned int wa_offset,
			    struct scatterlist *sg, unsigned int sg_offset,
			    unsigned int len)
{
	WARN_ON(!wa->address);

	scatterwalk_map_and_copy(wa->address + wa_offset, sg, sg_offset, len,
				 1);
}