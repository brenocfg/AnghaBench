#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int block_size; int /*<<< orphan*/  pi_prot_type; } ;
struct se_device {unsigned long long prot_length; TYPE_1__* transport; TYPE_2__ dev_attrib; } ;
struct TYPE_3__ {scalar_t__ (* get_blocks ) (struct se_device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int FDBD_FORMAT_UNIT_SIZE ; 
 int fd_do_prot_fill (struct se_device*,int /*<<< orphan*/ ,scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ stub1 (struct se_device*) ; 
 scalar_t__ stub2 (struct se_device*) ; 
 int /*<<< orphan*/  vfree (unsigned char*) ; 
 unsigned char* vzalloc (int) ; 

__attribute__((used)) static int fd_format_prot(struct se_device *dev)
{
	unsigned char *buf;
	int unit_size = FDBD_FORMAT_UNIT_SIZE * dev->dev_attrib.block_size;
	int ret;

	if (!dev->dev_attrib.pi_prot_type) {
		pr_err("Unable to format_prot while pi_prot_type == 0\n");
		return -ENODEV;
	}

	buf = vzalloc(unit_size);
	if (!buf) {
		pr_err("Unable to allocate FILEIO prot buf\n");
		return -ENOMEM;
	}

	pr_debug("Using FILEIO prot_length: %llu\n",
		 (unsigned long long)(dev->transport->get_blocks(dev) + 1) *
					dev->prot_length);

	memset(buf, 0xff, unit_size);
	ret = fd_do_prot_fill(dev, 0, dev->transport->get_blocks(dev) + 1,
			      buf, unit_size);
	vfree(buf);
	return ret;
}