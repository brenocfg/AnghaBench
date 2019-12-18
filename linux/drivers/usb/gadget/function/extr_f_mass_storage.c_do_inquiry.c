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
struct fsg_lun {scalar_t__* inquiry_string; scalar_t__ removable; scalar_t__ cdrom; } ;
struct fsg_common {int bad_lun_okay; scalar_t__* inquiry_string; struct fsg_lun* curlun; } ;
struct fsg_buffhd {scalar_t__ buf; } ;

/* Variables and functions */
 int TYPE_DISK ; 
 int TYPE_NO_LUN ; 
 int TYPE_ROM ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_inquiry(struct fsg_common *common, struct fsg_buffhd *bh)
{
	struct fsg_lun *curlun = common->curlun;
	u8	*buf = (u8 *) bh->buf;

	if (!curlun) {		/* Unsupported LUNs are okay */
		common->bad_lun_okay = 1;
		memset(buf, 0, 36);
		buf[0] = TYPE_NO_LUN;	/* Unsupported, no device-type */
		buf[4] = 31;		/* Additional length */
		return 36;
	}

	buf[0] = curlun->cdrom ? TYPE_ROM : TYPE_DISK;
	buf[1] = curlun->removable ? 0x80 : 0;
	buf[2] = 2;		/* ANSI SCSI level 2 */
	buf[3] = 2;		/* SCSI-2 INQUIRY data format */
	buf[4] = 31;		/* Additional length */
	buf[5] = 0;		/* No special options */
	buf[6] = 0;
	buf[7] = 0;
	if (curlun->inquiry_string[0])
		memcpy(buf + 8, curlun->inquiry_string,
		       sizeof(curlun->inquiry_string));
	else
		memcpy(buf + 8, common->inquiry_string,
		       sizeof(common->inquiry_string));
	return 36;
}