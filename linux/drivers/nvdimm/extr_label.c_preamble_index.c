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
typedef  int /*<<< orphan*/  u32 ;
struct nvdimm_drvdata {int dummy; } ;
struct nd_namespace_index {int /*<<< orphan*/  nslot; scalar_t__ free; } ;

/* Variables and functions */
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct nd_namespace_index* to_namespace_index (struct nvdimm_drvdata*,int) ; 

__attribute__((used)) static bool preamble_index(struct nvdimm_drvdata *ndd, int idx,
		struct nd_namespace_index **nsindex_out,
		unsigned long **free, u32 *nslot)
{
	struct nd_namespace_index *nsindex;

	nsindex = to_namespace_index(ndd, idx);
	if (nsindex == NULL)
		return false;

	*free = (unsigned long *) nsindex->free;
	*nslot = __le32_to_cpu(nsindex->nslot);
	*nsindex_out = nsindex;

	return true;
}