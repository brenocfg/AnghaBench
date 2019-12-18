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
struct device {int dummy; } ;
struct rproc {int table_sz; TYPE_1__* table_ptr; struct device dev; } ;
struct fw_rsc_hdr {size_t type; } ;
typedef  int (* rproc_handle_resource_t ) (struct rproc*,void*,int,int) ;
struct TYPE_2__ {int num; int* offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int RSC_HANDLED ; 
 size_t RSC_LAST ; 
 size_t RSC_VENDOR_END ; 
 size_t RSC_VENDOR_START ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,size_t) ; 
 int rproc_handle_rsc (struct rproc*,size_t,void*,int,int) ; 

__attribute__((used)) static int rproc_handle_resources(struct rproc *rproc,
				  rproc_handle_resource_t handlers[RSC_LAST])
{
	struct device *dev = &rproc->dev;
	rproc_handle_resource_t handler;
	int ret = 0, i;

	if (!rproc->table_ptr)
		return 0;

	for (i = 0; i < rproc->table_ptr->num; i++) {
		int offset = rproc->table_ptr->offset[i];
		struct fw_rsc_hdr *hdr = (void *)rproc->table_ptr + offset;
		int avail = rproc->table_sz - offset - sizeof(*hdr);
		void *rsc = (void *)hdr + sizeof(*hdr);

		/* make sure table isn't truncated */
		if (avail < 0) {
			dev_err(dev, "rsc table is truncated\n");
			return -EINVAL;
		}

		dev_dbg(dev, "rsc: type %d\n", hdr->type);

		if (hdr->type >= RSC_VENDOR_START &&
		    hdr->type <= RSC_VENDOR_END) {
			ret = rproc_handle_rsc(rproc, hdr->type, rsc,
					       offset + sizeof(*hdr), avail);
			if (ret == RSC_HANDLED)
				continue;
			else if (ret < 0)
				break;

			dev_warn(dev, "unsupported vendor resource %d\n",
				 hdr->type);
			continue;
		}

		if (hdr->type >= RSC_LAST) {
			dev_warn(dev, "unsupported resource %d\n", hdr->type);
			continue;
		}

		handler = handlers[hdr->type];
		if (!handler)
			continue;

		ret = handler(rproc, rsc, offset + sizeof(*hdr), avail);
		if (ret)
			break;
	}

	return ret;
}