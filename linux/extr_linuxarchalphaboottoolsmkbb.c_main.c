#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* bootblock_quadwords; scalar_t__ bootblock_checksum; int /*<<< orphan*/  bootblock_label; } ;
typedef  TYPE_1__ bootblock ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lseek (int,long,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int write (int,TYPE_1__*,int) ; 

int main(int argc, char ** argv)
{
    bootblock		bootblock_from_disk;
    bootblock		bootloader_image;
    int			dev, fd;
    int			i;
    int			nread;

    /* Make sure of the arg count */
    if(argc != 3) {
	fprintf(stderr, "Usage: %s device lxboot\n", argv[0]);
	exit(0);
    }

    /* First, open the device and make sure it's accessible */
    dev = open(argv[1], O_RDWR);
    if(dev < 0) {
	perror(argv[1]);
	exit(0);
    }

    /* Now open the lxboot and make sure it's reasonable */
    fd = open(argv[2], O_RDONLY);
    if(fd < 0) {
	perror(argv[2]);
	close(dev);
	exit(0);
    }

    /* Read in the lxboot */
    nread = read(fd, &bootloader_image, sizeof(bootblock));
    if(nread != sizeof(bootblock)) {
	perror("lxboot read");
	fprintf(stderr, "expected %zd, got %d\n", sizeof(bootblock), nread);
	exit(0);
    }

    /* Read in the bootblock from disk. */
    nread = read(dev, &bootblock_from_disk, sizeof(bootblock));
    if(nread != sizeof(bootblock)) {
	perror("bootblock read");
	fprintf(stderr, "expected %zd, got %d\n", sizeof(bootblock), nread);
	exit(0);
    }

    /* Swap the bootblock's disklabel into the bootloader */
    bootloader_image.bootblock_label = bootblock_from_disk.bootblock_label;

    /* Calculate the bootblock checksum */
    bootloader_image.bootblock_checksum = 0;
    for(i = 0; i < 63; i++) {
	bootloader_image.bootblock_checksum += 
			bootloader_image.bootblock_quadwords[i];
    }

    /* Write the whole thing out! */
    lseek(dev, 0L, SEEK_SET);
    if(write(dev, &bootloader_image, sizeof(bootblock)) != sizeof(bootblock)) {
	perror("bootblock write");
	exit(0);
    }

    close(fd);
    close(dev);
    exit(0);
}