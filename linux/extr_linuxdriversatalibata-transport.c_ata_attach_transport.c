#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  match; int /*<<< orphan*/ ** attrs; int /*<<< orphan*/ * class; } ;
struct TYPE_7__ {TYPE_1__ ac; } ;
struct scsi_transport_template {TYPE_2__ host_attrs; int /*<<< orphan*/  user_scan; int /*<<< orphan*/  eh_strategy_handler; } ;
struct ata_internal {struct scsi_transport_template t; int /*<<< orphan*/ ** dev_attrs; int /*<<< orphan*/ ** link_attrs; int /*<<< orphan*/ ** port_attrs; TYPE_2__ dev_attr_cont; TYPE_2__ link_attr_cont; } ;
struct TYPE_10__ {int /*<<< orphan*/  class; } ;
struct TYPE_9__ {int /*<<< orphan*/  class; } ;
struct TYPE_8__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int ATA_DEV_ATTRS ; 
 int ATA_LINK_ATTRS ; 
 int ATA_PORT_ATTRS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SETUP_DEV_ATTRIBUTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP_LINK_ATTRIBUTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP_PORT_ATTRIBUTE (int /*<<< orphan*/ ) ; 
 TYPE_5__ ata_dev_class ; 
 TYPE_4__ ata_link_class ; 
 TYPE_3__ ata_port_class ; 
 int /*<<< orphan*/  ata_scsi_error ; 
 int /*<<< orphan*/  ata_scsi_user_scan ; 
 int /*<<< orphan*/  ata_tdev_match ; 
 int /*<<< orphan*/  ata_tlink_match ; 
 int /*<<< orphan*/  ata_tport_match ; 
 int /*<<< orphan*/  class ; 
 int /*<<< orphan*/  dma_mode ; 
 int /*<<< orphan*/  ering ; 
 int /*<<< orphan*/  gscr ; 
 int /*<<< orphan*/  hw_sata_spd_limit ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  idle_irq ; 
 struct ata_internal* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_pmp_links ; 
 int /*<<< orphan*/  pio_mode ; 
 int /*<<< orphan*/  port_no ; 
 int /*<<< orphan*/  sata_spd ; 
 int /*<<< orphan*/  sata_spd_limit ; 
 int /*<<< orphan*/  spdn_cnt ; 
 int /*<<< orphan*/  transport_container_register (TYPE_2__*) ; 
 int /*<<< orphan*/  trim ; 
 int /*<<< orphan*/  xfer_mode ; 

struct scsi_transport_template *ata_attach_transport(void)
{
	struct ata_internal *i;
	int count;

	i = kzalloc(sizeof(struct ata_internal), GFP_KERNEL);
	if (!i)
		return NULL;

	i->t.eh_strategy_handler	= ata_scsi_error;
	i->t.user_scan			= ata_scsi_user_scan;

	i->t.host_attrs.ac.attrs = &i->port_attrs[0];
	i->t.host_attrs.ac.class = &ata_port_class.class;
	i->t.host_attrs.ac.match = ata_tport_match;
	transport_container_register(&i->t.host_attrs);

	i->link_attr_cont.ac.class = &ata_link_class.class;
	i->link_attr_cont.ac.attrs = &i->link_attrs[0];
	i->link_attr_cont.ac.match = ata_tlink_match;
	transport_container_register(&i->link_attr_cont);

	i->dev_attr_cont.ac.class = &ata_dev_class.class;
	i->dev_attr_cont.ac.attrs = &i->dev_attrs[0];
	i->dev_attr_cont.ac.match = ata_tdev_match;
	transport_container_register(&i->dev_attr_cont);

	count = 0;
	SETUP_PORT_ATTRIBUTE(nr_pmp_links);
	SETUP_PORT_ATTRIBUTE(idle_irq);
	SETUP_PORT_ATTRIBUTE(port_no);
	BUG_ON(count > ATA_PORT_ATTRS);
	i->port_attrs[count] = NULL;

	count = 0;
	SETUP_LINK_ATTRIBUTE(hw_sata_spd_limit);
	SETUP_LINK_ATTRIBUTE(sata_spd_limit);
	SETUP_LINK_ATTRIBUTE(sata_spd);
	BUG_ON(count > ATA_LINK_ATTRS);
	i->link_attrs[count] = NULL;

	count = 0;
	SETUP_DEV_ATTRIBUTE(class);
	SETUP_DEV_ATTRIBUTE(pio_mode);
	SETUP_DEV_ATTRIBUTE(dma_mode);
	SETUP_DEV_ATTRIBUTE(xfer_mode);
	SETUP_DEV_ATTRIBUTE(spdn_cnt);
	SETUP_DEV_ATTRIBUTE(ering);
	SETUP_DEV_ATTRIBUTE(id);
	SETUP_DEV_ATTRIBUTE(gscr);
	SETUP_DEV_ATTRIBUTE(trim);
	BUG_ON(count > ATA_DEV_ATTRS);
	i->dev_attrs[count] = NULL;

	return &i->t;
}