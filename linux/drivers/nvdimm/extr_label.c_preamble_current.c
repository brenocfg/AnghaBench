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
struct nvdimm_drvdata {int /*<<< orphan*/  ns_current; } ;
struct nd_namespace_index {int dummy; } ;

/* Variables and functions */
 int preamble_index (struct nvdimm_drvdata*,int /*<<< orphan*/ ,struct nd_namespace_index**,unsigned long**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool preamble_current(struct nvdimm_drvdata *ndd,
		struct nd_namespace_index **nsindex,
		unsigned long **free, u32 *nslot)
{
	return preamble_index(ndd, ndd->ns_current, nsindex,
			free, nslot);
}