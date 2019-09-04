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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct urb {unsigned char* transfer_buffer; scalar_t__ actual_length; int /*<<< orphan*/  status; struct cx231xx_dmaqueue* context; } ;
struct cx231xx_dmaqueue {int last_sav; int /*<<< orphan*/  partial_buf; scalar_t__ is_partial_line; } ;
struct cx231xx {int state; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int /*<<< orphan*/  ENOENT ; 
 int cx231xx_find_boundary_SAV_EAV (unsigned char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int cx231xx_find_next_SAV_EAV (unsigned char*,scalar_t__,scalar_t__*) ; 
 scalar_t__ cx231xx_get_vbi_line (struct cx231xx*,struct cx231xx_dmaqueue*,int,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  print_err_status (struct cx231xx*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cx231xx_isoc_vbi_copy(struct cx231xx *dev, struct urb *urb)
{
	struct cx231xx_dmaqueue *dma_q = urb->context;
	int rc = 1;
	unsigned char *p_buffer;
	u32 bytes_parsed = 0, buffer_size = 0;
	u8 sav_eav = 0;

	if (!dev)
		return 0;

	if (dev->state & DEV_DISCONNECTED)
		return 0;

	if (urb->status < 0) {
		print_err_status(dev, -1, urb->status);
		if (urb->status == -ENOENT)
			return 0;
	}

	/* get buffer pointer and length */
	p_buffer = urb->transfer_buffer;
	buffer_size = urb->actual_length;

	if (buffer_size > 0) {
		bytes_parsed = 0;

		if (dma_q->is_partial_line) {
			/* Handle the case where we were working on a partial
			   line */
			sav_eav = dma_q->last_sav;
		} else {
			/* Check for a SAV/EAV overlapping the
			   buffer boundary */

			sav_eav = cx231xx_find_boundary_SAV_EAV(p_buffer,
							  dma_q->partial_buf,
							  &bytes_parsed);
		}

		sav_eav &= 0xF0;
		/* Get the first line if we have some portion of an SAV/EAV from
		   the last buffer or a partial line */
		if (sav_eav) {
			bytes_parsed += cx231xx_get_vbi_line(dev, dma_q,
				sav_eav,		       /* SAV/EAV */
				p_buffer + bytes_parsed,       /* p_buffer */
				buffer_size - bytes_parsed);   /* buffer size */
		}

		/* Now parse data that is completely in this buffer */
		dma_q->is_partial_line = 0;

		while (bytes_parsed < buffer_size) {
			u32 bytes_used = 0;

			sav_eav = cx231xx_find_next_SAV_EAV(
				p_buffer + bytes_parsed,	/* p_buffer */
				buffer_size - bytes_parsed, /* buffer size */
				&bytes_used);	/* bytes used to get SAV/EAV */

			bytes_parsed += bytes_used;

			sav_eav &= 0xF0;
			if (sav_eav && (bytes_parsed < buffer_size)) {
				bytes_parsed += cx231xx_get_vbi_line(dev,
					dma_q, sav_eav,	/* SAV/EAV */
					p_buffer+bytes_parsed, /* p_buffer */
					buffer_size-bytes_parsed);/*buf size*/
			}
		}

		/* Save the last four bytes of the buffer so we can
		check the buffer boundary condition next time */
		memcpy(dma_q->partial_buf, p_buffer + buffer_size - 4, 4);
		bytes_parsed = 0;
	}

	return rc;
}