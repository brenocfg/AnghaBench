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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct vmw_private {int capabilities; int mmio_size; int last_read_seqno; int /*<<< orphan*/  marker_seq; void* traces_state; void* config_done_state; void* enable_state; int /*<<< orphan*/ * mmio_virt; } ;
struct vmw_fifo_state {int dx; int using_bounce_buffer; int /*<<< orphan*/  marker_queue; void* capabilities; int /*<<< orphan*/  rwsem; int /*<<< orphan*/  fifo_mutex; scalar_t__ reserved_size; int /*<<< orphan*/ * dynamic_buffer; int /*<<< orphan*/ * static_buffer; int /*<<< orphan*/  static_buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,...) ; 
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int SVGA_CAP_EXTENDED_FIFO ; 
 int SVGA_FIFO_BUSY ; 
 int SVGA_FIFO_CAPABILITIES ; 
 int SVGA_FIFO_FENCE ; 
 int SVGA_FIFO_MAX ; 
 int SVGA_FIFO_MIN ; 
 int SVGA_FIFO_NEXT_CMD ; 
 int SVGA_FIFO_STOP ; 
 int /*<<< orphan*/  SVGA_REG_BITS_PER_PIXEL ; 
 int /*<<< orphan*/  SVGA_REG_CONFIG_DONE ; 
 int /*<<< orphan*/  SVGA_REG_ENABLE ; 
 int SVGA_REG_ENABLE_ENABLE ; 
 int SVGA_REG_ENABLE_HIDE ; 
 int /*<<< orphan*/  SVGA_REG_HEIGHT ; 
 int /*<<< orphan*/  SVGA_REG_MEM_REGS ; 
 int /*<<< orphan*/  SVGA_REG_TRACES ; 
 int /*<<< orphan*/  SVGA_REG_WIDTH ; 
 int /*<<< orphan*/  VMWGFX_FIFO_STATIC_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_marker_queue_init (int /*<<< orphan*/ *) ; 
 void* vmw_mmio_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_mmio_write (int,int /*<<< orphan*/ *) ; 
 void* vmw_read (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_write (struct vmw_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

int vmw_fifo_init(struct vmw_private *dev_priv, struct vmw_fifo_state *fifo)
{
	u32  *fifo_mem = dev_priv->mmio_virt;
	uint32_t max;
	uint32_t min;

	fifo->dx = false;
	fifo->static_buffer_size = VMWGFX_FIFO_STATIC_SIZE;
	fifo->static_buffer = vmalloc(fifo->static_buffer_size);
	if (unlikely(fifo->static_buffer == NULL))
		return -ENOMEM;

	fifo->dynamic_buffer = NULL;
	fifo->reserved_size = 0;
	fifo->using_bounce_buffer = false;

	mutex_init(&fifo->fifo_mutex);
	init_rwsem(&fifo->rwsem);

	DRM_INFO("width %d\n", vmw_read(dev_priv, SVGA_REG_WIDTH));
	DRM_INFO("height %d\n", vmw_read(dev_priv, SVGA_REG_HEIGHT));
	DRM_INFO("bpp %d\n", vmw_read(dev_priv, SVGA_REG_BITS_PER_PIXEL));

	dev_priv->enable_state = vmw_read(dev_priv, SVGA_REG_ENABLE);
	dev_priv->config_done_state = vmw_read(dev_priv, SVGA_REG_CONFIG_DONE);
	dev_priv->traces_state = vmw_read(dev_priv, SVGA_REG_TRACES);

	vmw_write(dev_priv, SVGA_REG_ENABLE, SVGA_REG_ENABLE_ENABLE |
		  SVGA_REG_ENABLE_HIDE);
	vmw_write(dev_priv, SVGA_REG_TRACES, 0);

	min = 4;
	if (dev_priv->capabilities & SVGA_CAP_EXTENDED_FIFO)
		min = vmw_read(dev_priv, SVGA_REG_MEM_REGS);
	min <<= 2;

	if (min < PAGE_SIZE)
		min = PAGE_SIZE;

	vmw_mmio_write(min, fifo_mem + SVGA_FIFO_MIN);
	vmw_mmio_write(dev_priv->mmio_size, fifo_mem + SVGA_FIFO_MAX);
	wmb();
	vmw_mmio_write(min,  fifo_mem + SVGA_FIFO_NEXT_CMD);
	vmw_mmio_write(min,  fifo_mem + SVGA_FIFO_STOP);
	vmw_mmio_write(0, fifo_mem + SVGA_FIFO_BUSY);
	mb();

	vmw_write(dev_priv, SVGA_REG_CONFIG_DONE, 1);

	max = vmw_mmio_read(fifo_mem + SVGA_FIFO_MAX);
	min = vmw_mmio_read(fifo_mem  + SVGA_FIFO_MIN);
	fifo->capabilities = vmw_mmio_read(fifo_mem + SVGA_FIFO_CAPABILITIES);

	DRM_INFO("Fifo max 0x%08x min 0x%08x cap 0x%08x\n",
		 (unsigned int) max,
		 (unsigned int) min,
		 (unsigned int) fifo->capabilities);

	atomic_set(&dev_priv->marker_seq, dev_priv->last_read_seqno);
	vmw_mmio_write(dev_priv->last_read_seqno, fifo_mem + SVGA_FIFO_FENCE);
	vmw_marker_queue_init(&fifo->marker_queue);

	return 0;
}