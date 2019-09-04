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
struct simdisk {unsigned long size; int /*<<< orphan*/  lock; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (char) ; 
 unsigned long SECTOR_SHIFT ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  simc_lseek (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long simc_read (int /*<<< orphan*/ ,char*,unsigned long) ; 
 unsigned long simc_write (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void simdisk_transfer(struct simdisk *dev, unsigned long sector,
		unsigned long nsect, char *buffer, int write)
{
	unsigned long offset = sector << SECTOR_SHIFT;
	unsigned long nbytes = nsect << SECTOR_SHIFT;

	if (offset > dev->size || dev->size - offset < nbytes) {
		pr_notice("Beyond-end %s (%ld %ld)\n",
				write ? "write" : "read", offset, nbytes);
		return;
	}

	spin_lock(&dev->lock);
	while (nbytes > 0) {
		unsigned long io;

		simc_lseek(dev->fd, offset, SEEK_SET);
		READ_ONCE(*buffer);
		if (write)
			io = simc_write(dev->fd, buffer, nbytes);
		else
			io = simc_read(dev->fd, buffer, nbytes);
		if (io == -1) {
			pr_err("SIMDISK: IO error %d\n", errno);
			break;
		}
		buffer += io;
		offset += io;
		nbytes -= io;
	}
	spin_unlock(&dev->lock);
}