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
struct scsi_inq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * serial; } ;
struct aac_dev {TYPE_1__ adapter_info; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static int setinqserial(struct aac_dev *dev, void *data, int cid)
{
	/*
	 *	This breaks array migration.
	 */
	return snprintf((char *)(data), sizeof(struct scsi_inq) - 4, "%08X%02X",
			le32_to_cpu(dev->adapter_info.serial[0]), cid);
}