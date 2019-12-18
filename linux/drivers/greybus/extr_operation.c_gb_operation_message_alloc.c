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
typedef  int /*<<< orphan*/  u8 ;
struct gb_operation_msg_hdr {int dummy; } ;
struct gb_message {int /*<<< orphan*/  buffer; } ;
struct gb_host_device {size_t buffer_size_max; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 int /*<<< orphan*/  gb_message_cache ; 
 int /*<<< orphan*/  gb_operation_message_init (struct gb_host_device*,struct gb_message*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct gb_message*) ; 
 struct gb_message* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gb_message *
gb_operation_message_alloc(struct gb_host_device *hd, u8 type,
			   size_t payload_size, gfp_t gfp_flags)
{
	struct gb_message *message;
	struct gb_operation_msg_hdr *header;
	size_t message_size = payload_size + sizeof(*header);

	if (message_size > hd->buffer_size_max) {
		dev_warn(&hd->dev, "requested message size too big (%zu > %zu)\n",
			 message_size, hd->buffer_size_max);
		return NULL;
	}

	/* Allocate the message structure and buffer. */
	message = kmem_cache_zalloc(gb_message_cache, gfp_flags);
	if (!message)
		return NULL;

	message->buffer = kzalloc(message_size, gfp_flags);
	if (!message->buffer)
		goto err_free_message;

	/* Initialize the message.  Operation id is filled in later. */
	gb_operation_message_init(hd, message, 0, payload_size, type);

	return message;

err_free_message:
	kmem_cache_free(gb_message_cache, message);

	return NULL;
}