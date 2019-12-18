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

/* Variables and functions */
 int /*<<< orphan*/  FW_MGMT_IOC_SET_TIMEOUT_MS ; 
 char* FW_TAG_BCND_DEFAULT ; 
 char* FW_TAG_INT_DEFAULT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 char* firmware_tag ; 
 int fw_timeout ; 
 scalar_t__ fw_update_type ; 
 char* fwdev ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strtoul (char*,char**,int) ; 
 int update_backend_firmware (int) ; 
 int update_intf_firmware (int) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
	int fd, ret;
	char *endptr;

	if (argc > 1 &&
	    (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		usage();
		return -1;
	}

	if (argc > 1)
		fwdev = argv[1];

	if (argc > 2)
		fw_update_type = strtoul(argv[2], &endptr, 10);

	if (argc > 3)
		firmware_tag = argv[3];
	else if (!fw_update_type)
		firmware_tag = FW_TAG_INT_DEFAULT;
	else
		firmware_tag = FW_TAG_BCND_DEFAULT;

	if (argc > 4)
		fw_timeout = strtoul(argv[4], &endptr, 10);

	printf("Trying Firmware update: fwdev: %s, type: %s, tag: %s, timeout: %u\n",
		fwdev, fw_update_type == 0 ? "interface" : "backend",
		firmware_tag, fw_timeout);

	printf("Opening %s firmware management device\n", fwdev);

	fd = open(fwdev, O_RDWR);
	if (fd < 0) {
		printf("Failed to open: %s\n", fwdev);
		return -1;
	}

	/* Set Timeout */
	printf("Setting timeout to %u ms\n", fw_timeout);

	ret = ioctl(fd, FW_MGMT_IOC_SET_TIMEOUT_MS, &fw_timeout);
	if (ret < 0) {
		printf("Failed to set timeout: %s (%d)\n", fwdev, ret);
		ret = -1;
		goto close_fd;
	}

	if (!fw_update_type)
		ret = update_intf_firmware(fd);
	else
		ret = update_backend_firmware(fd);

close_fd:
	close(fd);

	return ret;
}