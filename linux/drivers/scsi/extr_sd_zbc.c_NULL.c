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
struct scsi_disk {int /*<<< orphan*/  device; } ;
struct gendisk {int dummy; } ;
struct blk_zone {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int get_unaligned_be32 (unsigned char*) ; 
 int /*<<< orphan*/  kvfree (unsigned char*) ; 
 unsigned int min (unsigned int,int) ; 
 struct scsi_disk* scsi_disk (struct gendisk*) ; 
 int /*<<< orphan*/  sd_is_zoned (struct scsi_disk*) ; 
 unsigned char* sd_zbc_alloc_report_buffer (struct scsi_disk*,unsigned int,size_t*) ; 
 int sd_zbc_do_report_zones (struct scsi_disk*,unsigned char*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_zbc_parse_report (struct scsi_disk*,unsigned char*,struct blk_zone*) ; 
 int /*<<< orphan*/  sectors_to_logical (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sd_zbc_report_zones(struct gendisk *disk, sector_t sector,
			struct blk_zone *zones, unsigned int *nr_zones)
{
	struct scsi_disk *sdkp = scsi_disk(disk);
	unsigned int i, nrz = *nr_zones;
	unsigned char *buf;
	size_t buflen = 0, offset = 0;
	int ret = 0;

	if (!sd_is_zoned(sdkp))
		/* Not a zoned device */
		return -EOPNOTSUPP;

	buf = sd_zbc_alloc_report_buffer(sdkp, nrz, &buflen);
	if (!buf)
		return -ENOMEM;

	ret = sd_zbc_do_report_zones(sdkp, buf, buflen,
			sectors_to_logical(sdkp->device, sector), true);
	if (ret)
		goto out;

	nrz = min(nrz, get_unaligned_be32(&buf[0]) / 64);
	for (i = 0; i < nrz; i++) {
		offset += 64;
		sd_zbc_parse_report(sdkp, buf + offset, zones);
		zones++;
	}

	*nr_zones = nrz;

out:
	kvfree(buf);

	return ret;
}