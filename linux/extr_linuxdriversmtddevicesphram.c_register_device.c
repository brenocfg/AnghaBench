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
struct TYPE_2__ {char* name; size_t size; int writesize; int /*<<< orphan*/  priv; int /*<<< orphan*/  erasesize; int /*<<< orphan*/  type; int /*<<< orphan*/  owner; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; int /*<<< orphan*/  _unpoint; int /*<<< orphan*/  _point; int /*<<< orphan*/  _erase; int /*<<< orphan*/  flags; } ;
struct phram_mtd_list {TYPE_1__ mtd; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_CAP_RAM ; 
 int /*<<< orphan*/  MTD_RAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct phram_mtd_list*) ; 
 struct phram_mtd_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mtd_device_register (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phram_erase ; 
 int /*<<< orphan*/  phram_list ; 
 int /*<<< orphan*/  phram_point ; 
 int /*<<< orphan*/  phram_read ; 
 int /*<<< orphan*/  phram_unpoint ; 
 int /*<<< orphan*/  phram_write ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int register_device(char *name, phys_addr_t start, size_t len)
{
	struct phram_mtd_list *new;
	int ret = -ENOMEM;

	new = kzalloc(sizeof(*new), GFP_KERNEL);
	if (!new)
		goto out0;

	ret = -EIO;
	new->mtd.priv = ioremap(start, len);
	if (!new->mtd.priv) {
		pr_err("ioremap failed\n");
		goto out1;
	}


	new->mtd.name = name;
	new->mtd.size = len;
	new->mtd.flags = MTD_CAP_RAM;
	new->mtd._erase = phram_erase;
	new->mtd._point = phram_point;
	new->mtd._unpoint = phram_unpoint;
	new->mtd._read = phram_read;
	new->mtd._write = phram_write;
	new->mtd.owner = THIS_MODULE;
	new->mtd.type = MTD_RAM;
	new->mtd.erasesize = PAGE_SIZE;
	new->mtd.writesize = 1;

	ret = -EAGAIN;
	if (mtd_device_register(&new->mtd, NULL, 0)) {
		pr_err("Failed to register new device\n");
		goto out2;
	}

	list_add_tail(&new->list, &phram_list);
	return 0;

out2:
	iounmap(new->mtd.priv);
out1:
	kfree(new);
out0:
	return ret;
}