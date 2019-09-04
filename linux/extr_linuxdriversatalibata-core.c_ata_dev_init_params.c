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
typedef  int u16 ;
struct ata_taskfile {int flags; int nsect; int device; int feature; int /*<<< orphan*/  protocol; int /*<<< orphan*/  command; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 unsigned int AC_ERR_DEV ; 
 unsigned int AC_ERR_INVALID ; 
 int ATA_ABORTED ; 
 int /*<<< orphan*/  ATA_CMD_INIT_DEV_PARAMS ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 

__attribute__((used)) static unsigned int ata_dev_init_params(struct ata_device *dev,
					u16 heads, u16 sectors)
{
	struct ata_taskfile tf;
	unsigned int err_mask;

	/* Number of sectors per track 1-255. Number of heads 1-16 */
	if (sectors < 1 || sectors > 255 || heads < 1 || heads > 16)
		return AC_ERR_INVALID;

	/* set up init dev params taskfile */
	DPRINTK("init dev params \n");

	ata_tf_init(dev, &tf);
	tf.command = ATA_CMD_INIT_DEV_PARAMS;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf.protocol = ATA_PROT_NODATA;
	tf.nsect = sectors;
	tf.device |= (heads - 1) & 0x0f; /* max head = num. of heads - 1 */

	err_mask = ata_exec_internal(dev, &tf, NULL, DMA_NONE, NULL, 0, 0);
	/* A clean abort indicates an original or just out of spec drive
	   and we should continue as we issue the setup based on the
	   drive reported working geometry */
	if (err_mask == AC_ERR_DEV && (tf.feature & ATA_ABORTED))
		err_mask = 0;

	DPRINTK("EXIT, err_mask=%x\n", err_mask);
	return err_mask;
}