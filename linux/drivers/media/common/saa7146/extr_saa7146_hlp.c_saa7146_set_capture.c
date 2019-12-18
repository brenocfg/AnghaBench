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
typedef  scalar_t__ u32 ;
struct saa7146_vv {scalar_t__ last_field; } ;
struct saa7146_format {int /*<<< orphan*/  trans; } ;
struct TYPE_4__ {int dma_handle; } ;
struct saa7146_dev {TYPE_2__ d_rps0; struct saa7146_vv* vv_data; } ;
struct saa7146_buf {TYPE_1__* fmt; } ;
struct TYPE_3__ {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_CAP (char*,...) ; 
 scalar_t__ IS_PLANAR (int /*<<< orphan*/ ) ; 
 int MASK_12 ; 
 int MASK_27 ; 
 int MASK_28 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  MC2 ; 
 int /*<<< orphan*/  PROT_ADDR1 ; 
 int /*<<< orphan*/  RPS_ADDR0 ; 
 scalar_t__ V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_FIELD_TOP ; 
 int /*<<< orphan*/  calculate_video_dma_grab_packed (struct saa7146_dev*,struct saa7146_buf*) ; 
 int /*<<< orphan*/  calculate_video_dma_grab_planar (struct saa7146_dev*,struct saa7146_buf*) ; 
 int /*<<< orphan*/  program_capture_engine (struct saa7146_dev*,int) ; 
 int /*<<< orphan*/  saa7146_disable_clipping (struct saa7146_dev*) ; 
 struct saa7146_format* saa7146_format_by_fourcc (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_set_output_format (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_set_window (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 

void saa7146_set_capture(struct saa7146_dev *dev, struct saa7146_buf *buf, struct saa7146_buf *next)
{
	struct saa7146_format *sfmt = saa7146_format_by_fourcc(dev,buf->fmt->pixelformat);
	struct saa7146_vv *vv = dev->vv_data;
	u32 vdma1_prot_addr;

	DEB_CAP("buf:%p, next:%p\n", buf, next);

	vdma1_prot_addr = saa7146_read(dev, PROT_ADDR1);
	if( 0 == vdma1_prot_addr ) {
		/* clear out beginning of streaming bit (rps register 0)*/
		DEB_CAP("forcing sync to new frame\n");
		saa7146_write(dev, MC2, MASK_27 );
	}

	saa7146_set_window(dev, buf->fmt->width, buf->fmt->height, buf->fmt->field);
	saa7146_set_output_format(dev, sfmt->trans);
	saa7146_disable_clipping(dev);

	if ( vv->last_field == V4L2_FIELD_INTERLACED ) {
	} else if ( vv->last_field == V4L2_FIELD_TOP ) {
		vv->last_field = V4L2_FIELD_BOTTOM;
	} else if ( vv->last_field == V4L2_FIELD_BOTTOM ) {
		vv->last_field = V4L2_FIELD_TOP;
	}

	if( 0 != IS_PLANAR(sfmt->trans)) {
		calculate_video_dma_grab_planar(dev, buf);
		program_capture_engine(dev,1);
	} else {
		calculate_video_dma_grab_packed(dev, buf);
		program_capture_engine(dev,0);
	}

/*
	printk("vdma%d.base_even:     0x%08x\n", 1,saa7146_read(dev,BASE_EVEN1));
	printk("vdma%d.base_odd:      0x%08x\n", 1,saa7146_read(dev,BASE_ODD1));
	printk("vdma%d.prot_addr:     0x%08x\n", 1,saa7146_read(dev,PROT_ADDR1));
	printk("vdma%d.base_page:     0x%08x\n", 1,saa7146_read(dev,BASE_PAGE1));
	printk("vdma%d.pitch:         0x%08x\n", 1,saa7146_read(dev,PITCH1));
	printk("vdma%d.num_line_byte: 0x%08x\n", 1,saa7146_read(dev,NUM_LINE_BYTE1));
	printk("vdma%d => vptr      : 0x%08x\n", 1,saa7146_read(dev,PCI_VDP1));
*/

	/* write the address of the rps-program */
	saa7146_write(dev, RPS_ADDR0, dev->d_rps0.dma_handle);

	/* turn on rps */
	saa7146_write(dev, MC1, (MASK_12 | MASK_28));
}