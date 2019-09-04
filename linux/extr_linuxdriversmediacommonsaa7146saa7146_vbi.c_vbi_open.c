#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  function; } ;
struct saa7146_vv {struct file* vbi_read_timeout_file; TYPE_3__ vbi_read_timeout; } ;
struct saa7146_fh {int /*<<< orphan*/  vbi_q; TYPE_1__* dev; } ;
struct saa7146_dev {TYPE_4__* ext_vv_data; int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  slock; TYPE_2__* pci; } ;
struct saa7146_buf {int dummy; } ;
struct file {struct saa7146_fh* private_data; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct saa7146_vv* vv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRS_CTRL ; 
 int /*<<< orphan*/  DEB_S (char*) ; 
 int /*<<< orphan*/  DEB_VBI (char*,...) ; 
 int EBUSY ; 
 int MASK_04 ; 
 int MASK_08 ; 
 int MASK_20 ; 
 int MASK_24 ; 
 int MASK_29 ; 
 int MASK_30 ; 
 int /*<<< orphan*/  MC2 ; 
 int /*<<< orphan*/  PCI_BT_V1 ; 
 int /*<<< orphan*/  RESOURCE_DMA3_BRS ; 
 int SAA7146_USE_PORT_B_FOR_VBI ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VBI_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_SEQ_TB ; 
 int saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int saa7146_res_get (struct saa7146_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vbi_qops ; 
 int /*<<< orphan*/  vbi_read_timeout ; 
 int vbi_workaround (struct saa7146_dev*) ; 
 int /*<<< orphan*/  videobuf_queue_sg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vbi_open(struct saa7146_dev *dev, struct file *file)
{
	struct saa7146_fh *fh = file->private_data;
	struct saa7146_vv *vv = fh->dev->vv_data;

	u32 arbtr_ctrl	= saa7146_read(dev, PCI_BT_V1);
	int ret = 0;

	DEB_VBI("dev:%p, fh:%p\n", dev, fh);

	ret = saa7146_res_get(fh, RESOURCE_DMA3_BRS);
	if (0 == ret) {
		DEB_S("cannot get vbi RESOURCE_DMA3_BRS resource\n");
		return -EBUSY;
	}

	/* adjust arbitrition control for video dma 3 */
	arbtr_ctrl &= ~0x1f0000;
	arbtr_ctrl |=  0x1d0000;
	saa7146_write(dev, PCI_BT_V1, arbtr_ctrl);
	saa7146_write(dev, MC2, (MASK_04|MASK_20));

	videobuf_queue_sg_init(&fh->vbi_q, &vbi_qops,
			    &dev->pci->dev, &dev->slock,
			    V4L2_BUF_TYPE_VBI_CAPTURE,
			    V4L2_FIELD_SEQ_TB, // FIXME: does this really work?
			    sizeof(struct saa7146_buf),
			    file, &dev->v4l2_lock);

	vv->vbi_read_timeout.function = vbi_read_timeout;
	vv->vbi_read_timeout_file = file;

	/* initialize the brs */
	if ( 0 != (SAA7146_USE_PORT_B_FOR_VBI & dev->ext_vv_data->flags)) {
		saa7146_write(dev, BRS_CTRL, MASK_30|MASK_29 | (7 << 19));
	} else {
		saa7146_write(dev, BRS_CTRL, 0x00000001);

		if (0 != (ret = vbi_workaround(dev))) {
			DEB_VBI("vbi workaround failed!\n");
			/* return ret;*/
		}
	}

	/* upload brs register */
	saa7146_write(dev, MC2, (MASK_08|MASK_24));
	return 0;
}