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
struct zorro_dev {int /*<<< orphan*/  slotsize; int /*<<< orphan*/  slotaddr; int /*<<< orphan*/  rom; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
struct ConfigDev {void* cd_BoardSize; void* cd_BoardAddr; void* cd_SlotSize; void* cd_SlotAddr; int /*<<< orphan*/  cd_Rom; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  cd ;

/* Variables and functions */
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  memory_read_from_buffer (char*,size_t,int /*<<< orphan*/ *,struct ConfigDev*,int) ; 
 int /*<<< orphan*/  memset (struct ConfigDev*,int /*<<< orphan*/ ,int) ; 
 struct zorro_dev* to_zorro_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zorro_resource_len (struct zorro_dev*) ; 
 int /*<<< orphan*/  zorro_resource_start (struct zorro_dev*) ; 

__attribute__((used)) static ssize_t zorro_read_config(struct file *filp, struct kobject *kobj,
				 struct bin_attribute *bin_attr,
				 char *buf, loff_t off, size_t count)
{
	struct zorro_dev *z = to_zorro_dev(kobj_to_dev(kobj));
	struct ConfigDev cd;

	/* Construct a ConfigDev */
	memset(&cd, 0, sizeof(cd));
	cd.cd_Rom = z->rom;
	cd.cd_SlotAddr = cpu_to_be16(z->slotaddr);
	cd.cd_SlotSize = cpu_to_be16(z->slotsize);
	cd.cd_BoardAddr = cpu_to_be32(zorro_resource_start(z));
	cd.cd_BoardSize = cpu_to_be32(zorro_resource_len(z));

	return memory_read_from_buffer(buf, count, &off, &cd, sizeof(cd));
}