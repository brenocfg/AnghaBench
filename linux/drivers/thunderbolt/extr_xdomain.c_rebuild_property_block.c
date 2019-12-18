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
typedef  int u32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int tb_property_format_dir (int /*<<< orphan*/ ,int*,int) ; 
 int* xdomain_property_block ; 
 int /*<<< orphan*/  xdomain_property_block_gen ; 
 int xdomain_property_block_len ; 
 int /*<<< orphan*/  xdomain_property_dir ; 

__attribute__((used)) static int rebuild_property_block(void)
{
	u32 *block, len;
	int ret;

	ret = tb_property_format_dir(xdomain_property_dir, NULL, 0);
	if (ret < 0)
		return ret;

	len = ret;

	block = kcalloc(len, sizeof(u32), GFP_KERNEL);
	if (!block)
		return -ENOMEM;

	ret = tb_property_format_dir(xdomain_property_dir, block, len);
	if (ret) {
		kfree(block);
		return ret;
	}

	kfree(xdomain_property_block);
	xdomain_property_block = block;
	xdomain_property_block_len = len;
	xdomain_property_block_gen++;

	return 0;
}