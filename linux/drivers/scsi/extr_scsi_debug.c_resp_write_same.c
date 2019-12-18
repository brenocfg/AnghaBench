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
typedef  int u64 ;
typedef  int u32 ;
struct scsi_cmnd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  atomic_rw ; 
 int check_device_access_params (struct scsi_cmnd*,int,int,int) ; 
 int do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fake_storep ; 
 int fetch_to_dev_buffer (struct scsi_cmnd*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  map_region (int,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_name ; 
 scalar_t__ scsi_debug_lbp () ; 
 int sdebug_sector_size ; 
 int /*<<< orphan*/  sdebug_store_sectors ; 
 scalar_t__ sdebug_verbose ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  unmap_region (int,int) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int resp_write_same(struct scsi_cmnd *scp, u64 lba, u32 num,
			   u32 ei_lba, bool unmap, bool ndob)
{
	int ret;
	unsigned long iflags;
	unsigned long long i;
	u32 lb_size = sdebug_sector_size;
	u64 block, lbaa;
	u8 *fs1p;

	ret = check_device_access_params(scp, lba, num, true);
	if (ret)
		return ret;

	write_lock_irqsave(&atomic_rw, iflags);

	if (unmap && scsi_debug_lbp()) {
		unmap_region(lba, num);
		goto out;
	}
	lbaa = lba;
	block = do_div(lbaa, sdebug_store_sectors);
	/* if ndob then zero 1 logical block, else fetch 1 logical block */
	fs1p = fake_storep + (block * lb_size);
	if (ndob) {
		memset(fs1p, 0, lb_size);
		ret = 0;
	} else
		ret = fetch_to_dev_buffer(scp, fs1p, lb_size);

	if (-1 == ret) {
		write_unlock_irqrestore(&atomic_rw, iflags);
		return DID_ERROR << 16;
	} else if (sdebug_verbose && !ndob && (ret < lb_size))
		sdev_printk(KERN_INFO, scp->device,
			    "%s: %s: lb size=%u, IO sent=%d bytes\n",
			    my_name, "write same", lb_size, ret);

	/* Copy first sector to remaining blocks */
	for (i = 1 ; i < num ; i++) {
		lbaa = lba + i;
		block = do_div(lbaa, sdebug_store_sectors);
		memmove(fake_storep + (block * lb_size), fs1p, lb_size);
	}
	if (scsi_debug_lbp())
		map_region(lba, num);
out:
	write_unlock_irqrestore(&atomic_rw, iflags);

	return 0;
}