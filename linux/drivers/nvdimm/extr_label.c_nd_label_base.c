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
struct nvdimm_drvdata {int dummy; } ;
typedef  void nd_namespace_label ;

/* Variables and functions */
 int sizeof_namespace_index (struct nvdimm_drvdata*) ; 
 void* to_namespace_index (struct nvdimm_drvdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nd_namespace_label *nd_label_base(struct nvdimm_drvdata *ndd)
{
	void *base = to_namespace_index(ndd, 0);

	return base + 2 * sizeof_namespace_index(ndd);
}