#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct nvdimm_drvdata {int /*<<< orphan*/  dev; } ;
struct nd_region {int /*<<< orphan*/  dev; struct nd_interleave_set* nd_set; struct nd_mapping* mapping; } ;
struct nd_namespace_label {scalar_t__ isetcookie; scalar_t__ lbasize; char* uuid; scalar_t__ dpa; int /*<<< orphan*/  name; int /*<<< orphan*/  abstraction_guid; int /*<<< orphan*/  type_guid; } ;
struct device {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * type; } ;
struct TYPE_2__ {int /*<<< orphan*/  claim_class; struct device dev; } ;
struct nd_namespace_blk {int id; void* alt_name; void* uuid; TYPE_1__ common; int /*<<< orphan*/ * lbasize; } ;
struct nd_mapping {int dummy; } ;
struct nd_interleave_set {int /*<<< orphan*/ * cookie2; int /*<<< orphan*/  type_guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 struct device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NSLABEL_NAME_LEN ; 
 int NSLABEL_UUID_LEN ; 
 scalar_t__ __cpu_to_le64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * __le64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  abstraction_guid ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  guid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* kmemdup (char*,int,int /*<<< orphan*/ ) ; 
 struct nd_namespace_blk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  namespace_blk_device_type ; 
 int /*<<< orphan*/  namespace_blk_release (struct device*) ; 
 scalar_t__ namespace_label_has (struct nvdimm_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_dbg_dpa (struct nd_region*,struct nvdimm_drvdata*,struct resource*,char*,int) ; 
 struct resource* nsblk_add_resource (struct nd_region*,struct nvdimm_drvdata*,struct nd_namespace_blk*,int /*<<< orphan*/ *) ; 
 struct nvdimm_drvdata* to_ndd (struct nd_mapping*) ; 
 int /*<<< orphan*/  to_nvdimm_cclass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_guid ; 

__attribute__((used)) static struct device *create_namespace_blk(struct nd_region *nd_region,
		struct nd_namespace_label *nd_label, int count)
{

	struct nd_mapping *nd_mapping = &nd_region->mapping[0];
	struct nd_interleave_set *nd_set = nd_region->nd_set;
	struct nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	struct nd_namespace_blk *nsblk;
	char name[NSLABEL_NAME_LEN];
	struct device *dev = NULL;
	struct resource *res;

	if (namespace_label_has(ndd, type_guid)) {
		if (!guid_equal(&nd_set->type_guid, &nd_label->type_guid)) {
			dev_dbg(ndd->dev, "expect type_guid %pUb got %pUb\n",
					&nd_set->type_guid,
					&nd_label->type_guid);
			return ERR_PTR(-EAGAIN);
		}

		if (nd_label->isetcookie != __cpu_to_le64(nd_set->cookie2)) {
			dev_dbg(ndd->dev, "expect cookie %#llx got %#llx\n",
					nd_set->cookie2,
					__le64_to_cpu(nd_label->isetcookie));
			return ERR_PTR(-EAGAIN);
		}
	}

	nsblk = kzalloc(sizeof(*nsblk), GFP_KERNEL);
	if (!nsblk)
		return ERR_PTR(-ENOMEM);
	dev = &nsblk->common.dev;
	dev->type = &namespace_blk_device_type;
	dev->parent = &nd_region->dev;
	nsblk->id = -1;
	nsblk->lbasize = __le64_to_cpu(nd_label->lbasize);
	nsblk->uuid = kmemdup(nd_label->uuid, NSLABEL_UUID_LEN,
			GFP_KERNEL);
	if (namespace_label_has(ndd, abstraction_guid))
		nsblk->common.claim_class
			= to_nvdimm_cclass(&nd_label->abstraction_guid);
	if (!nsblk->uuid)
		goto blk_err;
	memcpy(name, nd_label->name, NSLABEL_NAME_LEN);
	if (name[0]) {
		nsblk->alt_name = kmemdup(name, NSLABEL_NAME_LEN,
				GFP_KERNEL);
		if (!nsblk->alt_name)
			goto blk_err;
	}
	res = nsblk_add_resource(nd_region, ndd, nsblk,
			__le64_to_cpu(nd_label->dpa));
	if (!res)
		goto blk_err;
	nd_dbg_dpa(nd_region, ndd, res, "%d: assign\n", count);
	return dev;
 blk_err:
	namespace_blk_release(dev);
	return ERR_PTR(-ENXIO);
}