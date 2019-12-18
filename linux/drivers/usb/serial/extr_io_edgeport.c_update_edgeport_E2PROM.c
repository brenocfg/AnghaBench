#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ihex_binrec {int* data; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct firmware {scalar_t__ data; } ;
struct TYPE_6__ {int MajorVersion; int MinorVersion; int /*<<< orphan*/  BuildNumber; } ;
struct TYPE_5__ {int iDownloadFile; } ;
struct edgeport_serial {TYPE_4__* serial; TYPE_2__ boot_descriptor; TYPE_1__ product_info; } ;
struct device {int dummy; } ;
typedef  int __u8 ;
typedef  int __u32 ;
typedef  int __u16 ;
struct TYPE_8__ {TYPE_3__* dev; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
#define  EDGE_DOWNLOAD_FILE_80251 129 
#define  EDGE_DOWNLOAD_FILE_I930 128 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct ihex_binrec* ihex_next_binrec (struct ihex_binrec const*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_ihex_firmware (struct firmware const**,char const*,struct device*) ; 
 int rom_write (TYPE_4__*,int,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void update_edgeport_E2PROM(struct edgeport_serial *edge_serial)
{
	struct device *dev = &edge_serial->serial->dev->dev;
	__u32 BootCurVer;
	__u32 BootNewVer;
	__u8 BootMajorVersion;
	__u8 BootMinorVersion;
	__u16 BootBuildNumber;
	__u32 Bootaddr;
	const struct ihex_binrec *rec;
	const struct firmware *fw;
	const char *fw_name;
	int response;

	switch (edge_serial->product_info.iDownloadFile) {
	case EDGE_DOWNLOAD_FILE_I930:
		fw_name	= "edgeport/boot.fw";
		break;
	case EDGE_DOWNLOAD_FILE_80251:
		fw_name	= "edgeport/boot2.fw";
		break;
	default:
		return;
	}

	response = request_ihex_firmware(&fw, fw_name,
					 &edge_serial->serial->dev->dev);
	if (response) {
		dev_err(dev, "Failed to load image \"%s\" err %d\n",
		       fw_name, response);
		return;
	}

	rec = (const struct ihex_binrec *)fw->data;
	BootMajorVersion = rec->data[0];
	BootMinorVersion = rec->data[1];
	BootBuildNumber = (rec->data[2] << 8) | rec->data[3];

	/* Check Boot Image Version */
	BootCurVer = (edge_serial->boot_descriptor.MajorVersion << 24) +
		     (edge_serial->boot_descriptor.MinorVersion << 16) +
		      le16_to_cpu(edge_serial->boot_descriptor.BuildNumber);

	BootNewVer = (BootMajorVersion << 24) +
		     (BootMinorVersion << 16) +
		      BootBuildNumber;

	dev_dbg(dev, "Current Boot Image version %d.%d.%d\n",
	    edge_serial->boot_descriptor.MajorVersion,
	    edge_serial->boot_descriptor.MinorVersion,
	    le16_to_cpu(edge_serial->boot_descriptor.BuildNumber));


	if (BootNewVer > BootCurVer) {
		dev_dbg(dev, "**Update Boot Image from %d.%d.%d to %d.%d.%d\n",
		    edge_serial->boot_descriptor.MajorVersion,
		    edge_serial->boot_descriptor.MinorVersion,
		    le16_to_cpu(edge_serial->boot_descriptor.BuildNumber),
		    BootMajorVersion, BootMinorVersion, BootBuildNumber);

		dev_dbg(dev, "Downloading new Boot Image\n");

		for (rec = ihex_next_binrec(rec); rec;
		     rec = ihex_next_binrec(rec)) {
			Bootaddr = be32_to_cpu(rec->addr);
			response = rom_write(edge_serial->serial,
					     Bootaddr >> 16,
					     Bootaddr & 0xFFFF,
					     be16_to_cpu(rec->len),
					     &rec->data[0]);
			if (response < 0) {
				dev_err(&edge_serial->serial->dev->dev,
					"rom_write failed (%x, %x, %d)\n",
					Bootaddr >> 16, Bootaddr & 0xFFFF,
					be16_to_cpu(rec->len));
				break;
			}
		}
	} else {
		dev_dbg(dev, "Boot Image -- already up to date\n");
	}
	release_firmware(fw);
}