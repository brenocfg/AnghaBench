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
struct nd_namespace_label {int dummy; } ;

/* Variables and functions */
 scalar_t__ nd_label_base (struct nvdimm_drvdata*) ; 
 int sizeof_namespace_label (struct nvdimm_drvdata*) ; 

__attribute__((used)) static struct nd_namespace_label *to_label(struct nvdimm_drvdata *ndd, int slot)
{
	unsigned long label, base;

	base = (unsigned long) nd_label_base(ndd);
	label = base + sizeof_namespace_label(ndd) * slot;

	return (struct nd_namespace_label *) label;
}