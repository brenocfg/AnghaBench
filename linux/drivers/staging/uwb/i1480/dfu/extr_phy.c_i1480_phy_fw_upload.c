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
typedef  scalar_t__ u8 ;
struct i1480 {scalar_t__ phy_fw_name; int /*<<< orphan*/  dev; } ;
struct firmware {char* data; int size; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int i1480_mpi_read (struct i1480*,scalar_t__*,int,int) ; 
 int i1480_mpi_write (struct i1480*,char const*,size_t) ; 
 size_t min (size_t const,size_t) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,scalar_t__,int /*<<< orphan*/ ) ; 

int i1480_phy_fw_upload(struct i1480 *i1480)
{
	int result;
	const struct firmware *fw;
	const char *data_itr, *data_top;
	const size_t MAX_BLK_SIZE = 480;	/* 160 triads */
	size_t data_size;
	u8 phy_stat;

	result = request_firmware(&fw, i1480->phy_fw_name, i1480->dev);
	if (result < 0)
		goto out;
	/* Loop writing data in chunks as big as possible until done. */
	for (data_itr = fw->data, data_top = data_itr + fw->size;
	     data_itr < data_top; data_itr += MAX_BLK_SIZE) {
		data_size = min(MAX_BLK_SIZE, (size_t) (data_top - data_itr));
		result = i1480_mpi_write(i1480, data_itr, data_size);
		if (result < 0)
			goto error_mpi_write;
	}
	/* Read MPI page 0, offset 6; if 0, PHY was initialized correctly. */
	result = i1480_mpi_read(i1480, &phy_stat, 0x0006, 1);
	if (result < 0) {
		dev_err(i1480->dev, "PHY: can't get status: %d\n", result);
		goto error_mpi_status;
	}
	if (phy_stat != 0) {
		result = -ENODEV;
		dev_info(i1480->dev, "error, PHY not ready: %u\n", phy_stat);
		goto error_phy_status;
	}
	dev_info(i1480->dev, "PHY fw '%s': uploaded\n", i1480->phy_fw_name);
error_phy_status:
error_mpi_status:
error_mpi_write:
	release_firmware(fw);
	if (result < 0)
		dev_err(i1480->dev, "PHY fw '%s': failed to upload (%d), "
			"power cycle device\n", i1480->phy_fw_name, result);
out:
	return result;
}