#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  release; struct device* parent; } ;
struct TYPE_4__ {int n_links; TYPE_1__ dev; int /*<<< orphan*/  link_enable; int /*<<< orphan*/  send_break; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct fsi_master_hub {int size; TYPE_2__ master; struct fsi_device* upstream; int /*<<< orphan*/  addr; } ;
struct fsi_device {int /*<<< orphan*/  slave; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FSI_HUB_LINK_OFFSET ; 
 int FSI_HUB_LINK_SIZE ; 
 int /*<<< orphan*/  FSI_MVER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_of_node (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct fsi_master_hub*) ; 
 int fsi_device_read (struct fsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int fsi_master_register (TYPE_2__*) ; 
 int fsi_slave_claim_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsi_slave_release_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_device (TYPE_1__*) ; 
 int /*<<< orphan*/  hub_master_break ; 
 int /*<<< orphan*/  hub_master_init (struct fsi_master_hub*) ; 
 int /*<<< orphan*/  hub_master_link_enable ; 
 int /*<<< orphan*/  hub_master_read ; 
 int /*<<< orphan*/  hub_master_release ; 
 int /*<<< orphan*/  hub_master_write ; 
 struct fsi_master_hub* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_get (int /*<<< orphan*/ ) ; 
 struct fsi_device* to_fsi_dev (struct device*) ; 

__attribute__((used)) static int hub_master_probe(struct device *dev)
{
	struct fsi_device *fsi_dev = to_fsi_dev(dev);
	struct fsi_master_hub *hub;
	uint32_t reg, links;
	__be32 __reg;
	int rc;

	rc = fsi_device_read(fsi_dev, FSI_MVER, &__reg, sizeof(__reg));
	if (rc)
		return rc;

	reg = be32_to_cpu(__reg);
	links = (reg >> 8) & 0xff;
	dev_dbg(dev, "hub version %08x (%d links)\n", reg, links);

	rc = fsi_slave_claim_range(fsi_dev->slave, FSI_HUB_LINK_OFFSET,
			FSI_HUB_LINK_SIZE * links);
	if (rc) {
		dev_err(dev, "can't claim slave address range for links");
		return rc;
	}

	hub = kzalloc(sizeof(*hub), GFP_KERNEL);
	if (!hub) {
		rc = -ENOMEM;
		goto err_release;
	}

	hub->addr = FSI_HUB_LINK_OFFSET;
	hub->size = FSI_HUB_LINK_SIZE * links;
	hub->upstream = fsi_dev;

	hub->master.dev.parent = dev;
	hub->master.dev.release = hub_master_release;
	hub->master.dev.of_node = of_node_get(dev_of_node(dev));

	hub->master.n_links = links;
	hub->master.read = hub_master_read;
	hub->master.write = hub_master_write;
	hub->master.send_break = hub_master_break;
	hub->master.link_enable = hub_master_link_enable;

	dev_set_drvdata(dev, hub);

	hub_master_init(hub);

	rc = fsi_master_register(&hub->master);
	if (rc)
		goto err_release;

	/* At this point, fsi_master_register performs the device_initialize(),
	 * and holds the sole reference on master.dev. This means the device
	 * will be freed (via ->release) during any subsequent call to
	 * fsi_master_unregister.  We add our own reference to it here, so we
	 * can perform cleanup (in _remove()) without it being freed before
	 * we're ready.
	 */
	get_device(&hub->master.dev);
	return 0;

err_release:
	fsi_slave_release_range(fsi_dev->slave, FSI_HUB_LINK_OFFSET,
			FSI_HUB_LINK_SIZE * links);
	return rc;
}