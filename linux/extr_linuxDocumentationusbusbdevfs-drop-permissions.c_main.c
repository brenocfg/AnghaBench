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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int USBDEVFS_CAP_DROP_PRIVILEGES ; 
 int /*<<< orphan*/  USBDEVFS_GET_CAPABILITIES ; 
 int /*<<< orphan*/  claim_some_intf (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  drop_privileges (int,int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  reset_device (int) ; 
 int scanf (char*,int*) ; 

int main(int argc, char *argv[])
{
	uint32_t mask, caps;
	int c, fd;

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		printf("Failed to open file\n");
		goto err_fd;
	}

	/*
	 * check if dropping privileges is supported,
	 * bail on systems where the capability is not present
	 */
	ioctl(fd, USBDEVFS_GET_CAPABILITIES, &caps);
	if (!(caps & USBDEVFS_CAP_DROP_PRIVILEGES)) {
		printf("DROP_PRIVILEGES not supported\n");
		goto err;
	}

	/*
	 * Drop privileges but keep the ability to claim all
	 * free interfaces (i.e., those not used by kernel drivers)
	 */
	drop_privileges(fd, -1U);

	printf("Available options:\n"
		"[0] Exit now\n"
		"[1] Reset device. Should fail if device is in use\n"
		"[2] Claim 4 interfaces. Should succeed where not in use\n"
		"[3] Narrow interface permission mask\n"
		"Which option shall I run?: ");

	while (scanf("%d", &c) == 1) {
		switch (c) {
		case 0:
			goto exit;
		case 1:
			reset_device(fd);
			break;
		case 2:
			claim_some_intf(fd);
			break;
		case 3:
			printf("Insert new mask: ");
			scanf("%x", &mask);
			drop_privileges(fd, mask);
			break;
		default:
			printf("I don't recognize that\n");
		}

		printf("Which test shall I run next?: ");
	}

exit:
	close(fd);
	return 0;

err:
	close(fd);
err_fd:
	return 1;
}