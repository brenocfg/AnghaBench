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
struct mcu_msg_header {int length; int /*<<< orphan*/  type; } ;
struct allegro_mbox {unsigned int size; int /*<<< orphan*/  head; scalar_t__ data; } ;
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  sram; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  debug ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  msg_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,size_t,int) ; 

__attribute__((used)) static ssize_t allegro_mbox_read(struct allegro_dev *dev,
				 struct allegro_mbox *mbox,
				 void *dst, size_t nbyte)
{
	struct mcu_msg_header *header;
	unsigned int head;
	ssize_t size;
	size_t body_no_wrap;

	regmap_read(dev->sram, mbox->head, &head);
	if (head > mbox->size) {
		v4l2_err(&dev->v4l2_dev,
			 "invalid head (0x%x): must be smaller than mailbox size (0x%zx)\n",
			 head, mbox->size);
		return -EIO;
	}

	/* Assume that the header does not wrap. */
	regmap_bulk_read(dev->sram, mbox->data + head,
			 dst, sizeof(*header) / 4);
	header = dst;
	size = header->length + sizeof(*header);
	if (size > mbox->size || size & 0x3) {
		v4l2_err(&dev->v4l2_dev,
			 "invalid message length: %zu bytes (maximum %zu bytes)\n",
			 header->length + sizeof(*header), mbox->size);
		return -EIO;
	}
	if (size > nbyte) {
		v4l2_err(&dev->v4l2_dev,
			 "destination buffer too small: %zu bytes (need %zu bytes)\n",
			 nbyte, size);
		return -EINVAL;
	}

	/*
	 * The message might wrap within the mailbox. If the message does not
	 * wrap, the first read will read the entire message, otherwise the
	 * first read will read message until the end of the mailbox and the
	 * second read will read the remaining bytes from the beginning of the
	 * mailbox.
	 *
	 * Skip the header, as was already read to get the size of the body.
	 */
	body_no_wrap = min((size_t)header->length,
			   (size_t)(mbox->size - (head + sizeof(*header))));
	regmap_bulk_read(dev->sram, mbox->data + head + sizeof(*header),
			 dst + sizeof(*header), body_no_wrap / 4);
	regmap_bulk_read(dev->sram, mbox->data,
			 dst + sizeof(*header) + body_no_wrap,
			 (header->length - body_no_wrap) / 4);

	regmap_write(dev->sram, mbox->head, (head + size) % mbox->size);

	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "read status message: type %s, body length %d\n",
		 msg_type_name(header->type), header->length);

	return size;
}