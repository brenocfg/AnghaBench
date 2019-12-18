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
struct mtd_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct mt76_dev {TYPE_2__ eeprom; TYPE_1__* dev; } ;
struct device_node {char* name; } ;
typedef  void* phandle ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct mtd_info*) ; 
 int PTR_ERR (struct mtd_info*) ; 
 void* be32_to_cpup (int /*<<< orphan*/  const*) ; 
 struct mtd_info* get_mtd_device_nm (char const*) ; 
 int mtd_read (struct mtd_info*,int,int,size_t*,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_phandle (void*) ; 
 void* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  put_mtd_device (struct mtd_info*) ; 

__attribute__((used)) static int
mt76_get_of_eeprom(struct mt76_dev *dev, int len)
{
#if defined(CONFIG_OF) && defined(CONFIG_MTD)
	struct device_node *np = dev->dev->of_node;
	struct mtd_info *mtd;
	const __be32 *list;
	const char *part;
	phandle phandle;
	int offset = 0;
	int size;
	size_t retlen;
	int ret;

	if (!np)
		return -ENOENT;

	list = of_get_property(np, "mediatek,mtd-eeprom", &size);
	if (!list)
		return -ENOENT;

	phandle = be32_to_cpup(list++);
	if (!phandle)
		return -ENOENT;

	np = of_find_node_by_phandle(phandle);
	if (!np)
		return -EINVAL;

	part = of_get_property(np, "label", NULL);
	if (!part)
		part = np->name;

	mtd = get_mtd_device_nm(part);
	if (IS_ERR(mtd)) {
		ret =  PTR_ERR(mtd);
		goto out_put_node;
	}

	if (size <= sizeof(*list)) {
		ret = -EINVAL;
		goto out_put_node;
	}

	offset = be32_to_cpup(list);
	ret = mtd_read(mtd, offset, len, &retlen, dev->eeprom.data);
	put_mtd_device(mtd);
	if (ret)
		goto out_put_node;

	if (retlen < len) {
		ret = -EINVAL;
		goto out_put_node;
	}

out_put_node:
	of_node_put(np);
	return ret;
#else
	return -ENOENT;
#endif
}