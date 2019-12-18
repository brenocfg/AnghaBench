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
struct scsi_sense_hdr {int dummy; } ;
struct scsi_disk {struct scsi_device* device; } ;
struct scsi_device {TYPE_1__* request_queue; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int rq_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 unsigned char ZBC_IN ; 
 unsigned char ZBC_REPORT_ZONE_PARTIAL ; 
 unsigned char ZI_REPORT_ZONES ; 
 int /*<<< orphan*/  driver_byte (int) ; 
 unsigned int get_unaligned_be32 (unsigned char*) ; 
 int /*<<< orphan*/  host_byte (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (scalar_t__,unsigned char*) ; 
 int scsi_execute_req (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,unsigned char*,unsigned int,struct scsi_sense_hdr*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,unsigned int,...) ; 

__attribute__((used)) static int sd_zbc_do_report_zones(struct scsi_disk *sdkp, unsigned char *buf,
				  unsigned int buflen, sector_t lba,
				  bool partial)
{
	struct scsi_device *sdp = sdkp->device;
	const int timeout = sdp->request_queue->rq_timeout;
	struct scsi_sense_hdr sshdr;
	unsigned char cmd[16];
	unsigned int rep_len;
	int result;

	memset(cmd, 0, 16);
	cmd[0] = ZBC_IN;
	cmd[1] = ZI_REPORT_ZONES;
	put_unaligned_be64(lba, &cmd[2]);
	put_unaligned_be32(buflen, &cmd[10]);
	if (partial)
		cmd[14] = ZBC_REPORT_ZONE_PARTIAL;

	result = scsi_execute_req(sdp, cmd, DMA_FROM_DEVICE,
				  buf, buflen, &sshdr,
				  timeout, SD_MAX_RETRIES, NULL);
	if (result) {
		sd_printk(KERN_ERR, sdkp,
			  "REPORT ZONES lba %llu failed with %d/%d\n",
			  (unsigned long long)lba,
			  host_byte(result), driver_byte(result));
		return -EIO;
	}

	rep_len = get_unaligned_be32(&buf[0]);
	if (rep_len < 64) {
		sd_printk(KERN_ERR, sdkp,
			  "REPORT ZONES report invalid length %u\n",
			  rep_len);
		return -EIO;
	}

	return 0;
}