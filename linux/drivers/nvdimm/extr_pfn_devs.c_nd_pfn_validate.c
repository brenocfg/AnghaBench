#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  scalar_t__ u64 ;
struct page {int dummy; } ;
struct nd_pfn_sb {char const* uuid; scalar_t__ signature; int /*<<< orphan*/  page_struct_size; int /*<<< orphan*/  page_size; int /*<<< orphan*/  mode; int /*<<< orphan*/  start_pad; scalar_t__ dataoff; int /*<<< orphan*/  align; int /*<<< orphan*/  version_minor; scalar_t__ end_trunc; scalar_t__ parent_uuid; scalar_t__ checksum; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct nd_pfn {scalar_t__ align; int mode; TYPE_2__ dev; scalar_t__ uuid; struct nd_namespace_common* ndns; struct nd_pfn_sb* pfn_sb; } ;
struct TYPE_4__ {scalar_t__ start; } ;
struct nd_namespace_io {TYPE_1__ res; } ;
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;
struct nd_gen_sb {int dummy; } ;
typedef  enum nd_pfn_mode { ____Placeholder_nd_pfn_mode } nd_pfn_mode ;

/* Variables and functions */
 char const* DAX_SIG ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,unsigned long) ; 
 unsigned long PAGE_SIZE ; 
#define  PFN_MODE_PMEM 129 
#define  PFN_MODE_RAM 128 
 int PFN_SIG_LEN ; 
 int /*<<< orphan*/  SZ_4K ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned long) ; 
 scalar_t__ cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,unsigned long,unsigned long,int,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 unsigned long ilog2 (scalar_t__) ; 
 int /*<<< orphan*/  is_memory (int /*<<< orphan*/ ) ; 
 scalar_t__ kmemdup (char const*,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (scalar_t__) ; 
 scalar_t__ memcmp (scalar_t__,char const*,int) ; 
 char* nd_dev_to_uuid (int /*<<< orphan*/ *) ; 
 int nd_pfn_clear_memmap_errors (struct nd_pfn*) ; 
 scalar_t__ nd_sb_checksum (struct nd_gen_sb*) ; 
 int /*<<< orphan*/  nd_supported_alignment (unsigned long) ; 
 unsigned long nvdimm_namespace_capacity (struct nd_namespace_common*) ; 
 scalar_t__ nvdimm_read_bytes (struct nd_namespace_common*,int /*<<< orphan*/ ,struct nd_pfn_sb*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_size (TYPE_1__*) ; 
 struct nd_namespace_io* to_nd_namespace_io (int /*<<< orphan*/ *) ; 

int nd_pfn_validate(struct nd_pfn *nd_pfn, const char *sig)
{
	u64 checksum, offset;
	enum nd_pfn_mode mode;
	struct nd_namespace_io *nsio;
	unsigned long align, start_pad;
	struct nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;
	struct nd_namespace_common *ndns = nd_pfn->ndns;
	const u8 *parent_uuid = nd_dev_to_uuid(&ndns->dev);

	if (!pfn_sb || !ndns)
		return -ENODEV;

	if (!is_memory(nd_pfn->dev.parent))
		return -ENODEV;

	if (nvdimm_read_bytes(ndns, SZ_4K, pfn_sb, sizeof(*pfn_sb), 0))
		return -ENXIO;

	if (memcmp(pfn_sb->signature, sig, PFN_SIG_LEN) != 0)
		return -ENODEV;

	checksum = le64_to_cpu(pfn_sb->checksum);
	pfn_sb->checksum = 0;
	if (checksum != nd_sb_checksum((struct nd_gen_sb *) pfn_sb))
		return -ENODEV;
	pfn_sb->checksum = cpu_to_le64(checksum);

	if (memcmp(pfn_sb->parent_uuid, parent_uuid, 16) != 0)
		return -ENODEV;

	if (__le16_to_cpu(pfn_sb->version_minor) < 1) {
		pfn_sb->start_pad = 0;
		pfn_sb->end_trunc = 0;
	}

	if (__le16_to_cpu(pfn_sb->version_minor) < 2)
		pfn_sb->align = 0;

	if (__le16_to_cpu(pfn_sb->version_minor) < 4) {
		pfn_sb->page_struct_size = cpu_to_le16(64);
		pfn_sb->page_size = cpu_to_le32(PAGE_SIZE);
	}

	switch (le32_to_cpu(pfn_sb->mode)) {
	case PFN_MODE_RAM:
	case PFN_MODE_PMEM:
		break;
	default:
		return -ENXIO;
	}

	align = le32_to_cpu(pfn_sb->align);
	offset = le64_to_cpu(pfn_sb->dataoff);
	start_pad = le32_to_cpu(pfn_sb->start_pad);
	if (align == 0)
		align = 1UL << ilog2(offset);
	mode = le32_to_cpu(pfn_sb->mode);

	if ((le32_to_cpu(pfn_sb->page_size) > PAGE_SIZE) &&
			(mode == PFN_MODE_PMEM)) {
		dev_err(&nd_pfn->dev,
				"init failed, page size mismatch %d\n",
				le32_to_cpu(pfn_sb->page_size));
		return -EOPNOTSUPP;
	}

	if ((le16_to_cpu(pfn_sb->page_struct_size) < sizeof(struct page)) &&
			(mode == PFN_MODE_PMEM)) {
		dev_err(&nd_pfn->dev,
				"init failed, struct page size mismatch %d\n",
				le16_to_cpu(pfn_sb->page_struct_size));
		return -EOPNOTSUPP;
	}

	/*
	 * Check whether the we support the alignment. For Dax if the
	 * superblock alignment is not matching, we won't initialize
	 * the device.
	 */
	if (!nd_supported_alignment(align) &&
			!memcmp(pfn_sb->signature, DAX_SIG, PFN_SIG_LEN)) {
		dev_err(&nd_pfn->dev, "init failed, alignment mismatch: "
				"%ld:%ld\n", nd_pfn->align, align);
		return -EOPNOTSUPP;
	}

	if (!nd_pfn->uuid) {
		/*
		 * When probing a namepace via nd_pfn_probe() the uuid
		 * is NULL (see: nd_pfn_devinit()) we init settings from
		 * pfn_sb
		 */
		nd_pfn->uuid = kmemdup(pfn_sb->uuid, 16, GFP_KERNEL);
		if (!nd_pfn->uuid)
			return -ENOMEM;
		nd_pfn->align = align;
		nd_pfn->mode = mode;
	} else {
		/*
		 * When probing a pfn / dax instance we validate the
		 * live settings against the pfn_sb
		 */
		if (memcmp(nd_pfn->uuid, pfn_sb->uuid, 16) != 0)
			return -ENODEV;

		/*
		 * If the uuid validates, but other settings mismatch
		 * return EINVAL because userspace has managed to change
		 * the configuration without specifying new
		 * identification.
		 */
		if (nd_pfn->align != align || nd_pfn->mode != mode) {
			dev_err(&nd_pfn->dev,
					"init failed, settings mismatch\n");
			dev_dbg(&nd_pfn->dev, "align: %lx:%lx mode: %d:%d\n",
					nd_pfn->align, align, nd_pfn->mode,
					mode);
			return -EINVAL;
		}
	}

	if (align > nvdimm_namespace_capacity(ndns)) {
		dev_err(&nd_pfn->dev, "alignment: %lx exceeds capacity %llx\n",
				align, nvdimm_namespace_capacity(ndns));
		return -EINVAL;
	}

	/*
	 * These warnings are verbose because they can only trigger in
	 * the case where the physical address alignment of the
	 * namespace has changed since the pfn superblock was
	 * established.
	 */
	nsio = to_nd_namespace_io(&ndns->dev);
	if (offset >= resource_size(&nsio->res)) {
		dev_err(&nd_pfn->dev, "pfn array size exceeds capacity of %s\n",
				dev_name(&ndns->dev));
		return -EBUSY;
	}

	if ((align && !IS_ALIGNED(nsio->res.start + offset + start_pad, align))
			|| !IS_ALIGNED(offset, PAGE_SIZE)) {
		dev_err(&nd_pfn->dev,
				"bad offset: %#llx dax disabled align: %#lx\n",
				offset, align);
		return -ENXIO;
	}

	return nd_pfn_clear_memmap_errors(nd_pfn);
}