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
struct nvdimm_drvdata {int /*<<< orphan*/  dev; } ;
struct nd_mapping {int dummy; } ;
struct nd_label_ent {int /*<<< orphan*/ * label; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_label_free_slot (struct nvdimm_drvdata*,int /*<<< orphan*/ ) ; 
 struct nvdimm_drvdata* to_ndd (struct nd_mapping*) ; 
 int /*<<< orphan*/  to_slot (struct nvdimm_drvdata*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reap_victim(struct nd_mapping *nd_mapping,
		struct nd_label_ent *victim)
{
	struct nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	u32 slot = to_slot(ndd, victim->label);

	dev_dbg(ndd->dev, "free: %d\n", slot);
	nd_label_free_slot(ndd, slot);
	victim->label = NULL;
}