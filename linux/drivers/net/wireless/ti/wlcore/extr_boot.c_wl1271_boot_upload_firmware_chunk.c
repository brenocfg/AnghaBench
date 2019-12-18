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
struct TYPE_2__ {int start; int size; } ;
struct wlcore_partition_set {TYPE_1__ mem; } ;
typedef  struct wlcore_partition_set u8 ;
typedef  int u32 ;
struct wl1271 {struct wlcore_partition_set* ptable; } ;
typedef  int /*<<< orphan*/  partition ;

/* Variables and functions */
 size_t CHUNK_SIZE ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PART_DOWN ; 
 int /*<<< orphan*/  kfree (struct wlcore_partition_set*) ; 
 struct wlcore_partition_set* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct wlcore_partition_set*,struct wlcore_partition_set*,size_t) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int wlcore_set_partition (struct wl1271*,struct wlcore_partition_set*) ; 
 int wlcore_write (struct wl1271*,int,struct wlcore_partition_set*,size_t,int) ; 

__attribute__((used)) static int wl1271_boot_upload_firmware_chunk(struct wl1271 *wl, void *buf,
					     size_t fw_data_len, u32 dest)
{
	struct wlcore_partition_set partition;
	int addr, chunk_num, partition_limit;
	u8 *p, *chunk;
	int ret;

	/* whal_FwCtrl_LoadFwImageSm() */

	wl1271_debug(DEBUG_BOOT, "starting firmware upload");

	wl1271_debug(DEBUG_BOOT, "fw_data_len %zd chunk_size %d",
		     fw_data_len, CHUNK_SIZE);

	if ((fw_data_len % 4) != 0) {
		wl1271_error("firmware length not multiple of four");
		return -EIO;
	}

	chunk = kmalloc(CHUNK_SIZE, GFP_KERNEL);
	if (!chunk) {
		wl1271_error("allocation for firmware upload chunk failed");
		return -ENOMEM;
	}

	memcpy(&partition, &wl->ptable[PART_DOWN], sizeof(partition));
	partition.mem.start = dest;
	ret = wlcore_set_partition(wl, &partition);
	if (ret < 0)
		goto out;

	/* 10.1 set partition limit and chunk num */
	chunk_num = 0;
	partition_limit = wl->ptable[PART_DOWN].mem.size;

	while (chunk_num < fw_data_len / CHUNK_SIZE) {
		/* 10.2 update partition, if needed */
		addr = dest + (chunk_num + 2) * CHUNK_SIZE;
		if (addr > partition_limit) {
			addr = dest + chunk_num * CHUNK_SIZE;
			partition_limit = chunk_num * CHUNK_SIZE +
				wl->ptable[PART_DOWN].mem.size;
			partition.mem.start = addr;
			ret = wlcore_set_partition(wl, &partition);
			if (ret < 0)
				goto out;
		}

		/* 10.3 upload the chunk */
		addr = dest + chunk_num * CHUNK_SIZE;
		p = buf + chunk_num * CHUNK_SIZE;
		memcpy(chunk, p, CHUNK_SIZE);
		wl1271_debug(DEBUG_BOOT, "uploading fw chunk 0x%p to 0x%x",
			     p, addr);
		ret = wlcore_write(wl, addr, chunk, CHUNK_SIZE, false);
		if (ret < 0)
			goto out;

		chunk_num++;
	}

	/* 10.4 upload the last chunk */
	addr = dest + chunk_num * CHUNK_SIZE;
	p = buf + chunk_num * CHUNK_SIZE;
	memcpy(chunk, p, fw_data_len % CHUNK_SIZE);
	wl1271_debug(DEBUG_BOOT, "uploading fw last chunk (%zd B) 0x%p to 0x%x",
		     fw_data_len % CHUNK_SIZE, p, addr);
	ret = wlcore_write(wl, addr, chunk, fw_data_len % CHUNK_SIZE, false);

out:
	kfree(chunk);
	return ret;
}