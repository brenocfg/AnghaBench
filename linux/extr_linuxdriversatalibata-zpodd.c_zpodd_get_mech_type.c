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
struct rm_feature_desc {int mech_type; scalar_t__ load; int eject; int /*<<< orphan*/  feature_code; } ;
struct ata_taskfile {int flags; int lbam; int /*<<< orphan*/  protocol; int /*<<< orphan*/  command; } ;
struct ata_device {int dummy; } ;
typedef  enum odd_mech_type { ____Placeholder_odd_mech_type } odd_mech_type ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_PROT_PIO ; 
 int /*<<< orphan*/  ATA_CMD_PACKET ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
#define  GPCMD_GET_CONFIGURATION 128 
 int ODD_MECH_TYPE_DRAWER ; 
 int ODD_MECH_TYPE_SLOT ; 
 int ODD_MECH_TYPE_UNSUPPORTED ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,char const*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum odd_mech_type zpodd_get_mech_type(struct ata_device *dev)
{
	char buf[16];
	unsigned int ret;
	struct rm_feature_desc *desc = (void *)(buf + 8);
	struct ata_taskfile tf;
	static const char cdb[] = {  GPCMD_GET_CONFIGURATION,
			2,      /* only 1 feature descriptor requested */
			0, 3,   /* 3, removable medium feature */
			0, 0, 0,/* reserved */
			0, sizeof(buf),
			0, 0, 0,
	};

	ata_tf_init(dev, &tf);
	tf.flags = ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf.command = ATA_CMD_PACKET;
	tf.protocol = ATAPI_PROT_PIO;
	tf.lbam = sizeof(buf);

	ret = ata_exec_internal(dev, &tf, cdb, DMA_FROM_DEVICE,
				buf, sizeof(buf), 0);
	if (ret)
		return ODD_MECH_TYPE_UNSUPPORTED;

	if (be16_to_cpu(desc->feature_code) != 3)
		return ODD_MECH_TYPE_UNSUPPORTED;

	if (desc->mech_type == 0 && desc->load == 0 && desc->eject == 1)
		return ODD_MECH_TYPE_SLOT;
	else if (desc->mech_type == 1 && desc->load == 0 && desc->eject == 1)
		return ODD_MECH_TYPE_DRAWER;
	else
		return ODD_MECH_TYPE_UNSUPPORTED;
}