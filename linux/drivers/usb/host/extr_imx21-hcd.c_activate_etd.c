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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct imx21 {scalar_t__ regs; int /*<<< orphan*/  dev; struct etd_priv* etd; } ;
struct etd_priv {int dma_handle; scalar_t__ len; scalar_t__ dmem_size; int active_count; int disactivated_frame; int last_int_frame; int last_req_frame; int /*<<< orphan*/  bounce_buffer; int /*<<< orphan*/ * submitted_dwords; int /*<<< orphan*/  activated_frame; int /*<<< orphan*/  cpu_buffer; int /*<<< orphan*/  dmem_offset; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG_FRAME (struct imx21*,struct etd_priv*,int /*<<< orphan*/ ) ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ TD_DIR_IN ; 
 int /*<<< orphan*/  USBH_ETDDONEEN ; 
 int /*<<< orphan*/  USBH_ETDDONESTAT ; 
 scalar_t__ USBH_ETDENSET ; 
 scalar_t__ USBH_FRMNUB ; 
 int /*<<< orphan*/  USBH_XBUFSTAT ; 
 int /*<<< orphan*/  USBH_XFILLSTAT ; 
 int /*<<< orphan*/  USBH_YBUFSTAT ; 
 int /*<<< orphan*/  USBH_YFILLSTAT ; 
 int /*<<< orphan*/  USB_ETDDMACHANLCLR ; 
 int /*<<< orphan*/  USB_ETDDMAEN ; 
 scalar_t__ USB_ETDSMSA (int) ; 
 int /*<<< orphan*/  activated ; 
 int /*<<< orphan*/  clear_toggle_bit (struct imx21*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_dmem (struct imx21*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  etd_readl (struct imx21*,int,int) ; 
 int /*<<< orphan*/  free_dmem (struct imx21*,struct etd_priv*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonisoc_urb_completed_for_etd (struct imx21*,struct etd_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  set_register_bits (struct imx21*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_toggle_bit (struct imx21*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unsuitable_for_dma (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void activate_etd(struct imx21 *imx21, int etd_num, u8 dir)
{
	u32 etd_mask = 1 << etd_num;
	struct etd_priv *etd = &imx21->etd[etd_num];

	if (etd->dma_handle && unsuitable_for_dma(etd->dma_handle)) {
		/* For non aligned isoc the condition below is always true */
		if (etd->len <= etd->dmem_size) {
			/* Fits into data memory, use PIO */
			if (dir != TD_DIR_IN) {
				copy_to_dmem(imx21,
						etd->dmem_offset,
						etd->cpu_buffer, etd->len);
			}
			etd->dma_handle = 0;

		} else {
			/* Too big for data memory, use bounce buffer */
			enum dma_data_direction dmadir;

			if (dir == TD_DIR_IN) {
				dmadir = DMA_FROM_DEVICE;
				etd->bounce_buffer = kmalloc(etd->len,
								GFP_ATOMIC);
			} else {
				dmadir = DMA_TO_DEVICE;
				etd->bounce_buffer = kmemdup(etd->cpu_buffer,
								etd->len,
								GFP_ATOMIC);
			}
			if (!etd->bounce_buffer) {
				dev_err(imx21->dev, "failed bounce alloc\n");
				goto err_bounce_alloc;
			}

			etd->dma_handle =
				dma_map_single(imx21->dev,
						etd->bounce_buffer,
						etd->len,
						dmadir);
			if (dma_mapping_error(imx21->dev, etd->dma_handle)) {
				dev_err(imx21->dev, "failed bounce map\n");
				goto err_bounce_map;
			}
		}
	}

	clear_toggle_bit(imx21, USBH_ETDDONESTAT, etd_mask);
	set_register_bits(imx21, USBH_ETDDONEEN, etd_mask);
	clear_toggle_bit(imx21, USBH_XFILLSTAT, etd_mask);
	clear_toggle_bit(imx21, USBH_YFILLSTAT, etd_mask);

	if (etd->dma_handle) {
		set_register_bits(imx21, USB_ETDDMACHANLCLR, etd_mask);
		clear_toggle_bit(imx21, USBH_XBUFSTAT, etd_mask);
		clear_toggle_bit(imx21, USBH_YBUFSTAT, etd_mask);
		writel(etd->dma_handle, imx21->regs + USB_ETDSMSA(etd_num));
		set_register_bits(imx21, USB_ETDDMAEN, etd_mask);
	} else {
		if (dir != TD_DIR_IN) {
			/* need to set for ZLP and PIO */
			set_toggle_bit(imx21, USBH_XFILLSTAT, etd_mask);
			set_toggle_bit(imx21, USBH_YFILLSTAT, etd_mask);
		}
	}

	DEBUG_LOG_FRAME(imx21, etd, activated);

#ifdef DEBUG
	if (!etd->active_count) {
		int i;
		etd->activated_frame = readl(imx21->regs + USBH_FRMNUB);
		etd->disactivated_frame = -1;
		etd->last_int_frame = -1;
		etd->last_req_frame = -1;

		for (i = 0; i < 4; i++)
			etd->submitted_dwords[i] = etd_readl(imx21, etd_num, i);
	}
#endif

	etd->active_count = 1;
	writel(etd_mask, imx21->regs + USBH_ETDENSET);
	return;

err_bounce_map:
	kfree(etd->bounce_buffer);

err_bounce_alloc:
	free_dmem(imx21, etd);
	nonisoc_urb_completed_for_etd(imx21, etd, -ENOMEM);
}