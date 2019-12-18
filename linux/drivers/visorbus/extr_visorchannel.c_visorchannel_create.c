#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ulong ;
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ size; } ;
struct visorchannel {int needs_lock; scalar_t__ physaddr; size_t nbytes; int /*<<< orphan*/  guid; int /*<<< orphan*/ * mapped; void* requested; TYPE_1__ chan_hdr; int /*<<< orphan*/  remove_lock; int /*<<< orphan*/  insert_lock; } ;
struct channel_header {int dummy; } ;
typedef  int /*<<< orphan*/  guid_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEMREMAP_WB ; 
 int /*<<< orphan*/  VISOR_DRV_NAME ; 
 int /*<<< orphan*/  guid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  guid_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 struct visorchannel* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* memremap (scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,size_t) ; 
 void* request_mem_region (scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visor_video_guid ; 
 int /*<<< orphan*/  visorchannel_destroy (struct visorchannel*) ; 
 int visorchannel_read (struct visorchannel*,int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 

struct visorchannel *visorchannel_create(u64 physaddr, gfp_t gfp,
					 const guid_t *guid, bool needs_lock)
{
	struct visorchannel *channel;
	int err;
	size_t size = sizeof(struct channel_header);

	if (physaddr == 0)
		return NULL;

	channel = kzalloc(sizeof(*channel), gfp);
	if (!channel)
		return NULL;
	channel->needs_lock = needs_lock;
	spin_lock_init(&channel->insert_lock);
	spin_lock_init(&channel->remove_lock);
	/*
	 * Video driver constains the efi framebuffer so it will get a conflict
	 * resource when requesting its full mem region. Since we are only
	 * using the efi framebuffer for video we can ignore this. Remember that
	 * we haven't requested it so we don't try to release later on.
	 */
	channel->requested = request_mem_region(physaddr, size, VISOR_DRV_NAME);
	if (!channel->requested && !guid_equal(guid, &visor_video_guid))
		/* we only care about errors if this is not the video channel */
		goto err_destroy_channel;
	channel->mapped = memremap(physaddr, size, MEMREMAP_WB);
	if (!channel->mapped) {
		release_mem_region(physaddr, size);
		goto err_destroy_channel;
	}
	channel->physaddr = physaddr;
	channel->nbytes = size;
	err = visorchannel_read(channel, 0, &channel->chan_hdr, size);
	if (err)
		goto err_destroy_channel;
	size = (ulong)channel->chan_hdr.size;
	memunmap(channel->mapped);
	if (channel->requested)
		release_mem_region(channel->physaddr, channel->nbytes);
	channel->mapped = NULL;
	channel->requested = request_mem_region(channel->physaddr, size,
						VISOR_DRV_NAME);
	if (!channel->requested && !guid_equal(guid, &visor_video_guid))
		/* we only care about errors if this is not the video channel */
		goto err_destroy_channel;
	channel->mapped = memremap(channel->physaddr, size, MEMREMAP_WB);
	if (!channel->mapped) {
		release_mem_region(channel->physaddr, size);
		goto err_destroy_channel;
	}
	channel->nbytes = size;
	guid_copy(&channel->guid, guid);
	return channel;

err_destroy_channel:
	visorchannel_destroy(channel);
	return NULL;
}