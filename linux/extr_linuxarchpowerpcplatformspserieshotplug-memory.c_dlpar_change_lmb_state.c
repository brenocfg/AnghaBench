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
struct TYPE_4__ {scalar_t__ offline; } ;
struct memory_block {TYPE_1__ dev; } ;
struct drmem_lmb {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int device_offline (TYPE_1__*) ; 
 int device_online (TYPE_1__*) ; 
 struct memory_block* lmb_to_memblock (struct drmem_lmb*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static int dlpar_change_lmb_state(struct drmem_lmb *lmb, bool online)
{
	struct memory_block *mem_block;
	int rc;

	mem_block = lmb_to_memblock(lmb);
	if (!mem_block)
		return -EINVAL;

	if (online && mem_block->dev.offline)
		rc = device_online(&mem_block->dev);
	else if (!online && !mem_block->dev.offline)
		rc = device_offline(&mem_block->dev);
	else
		rc = 0;

	put_device(&mem_block->dev);

	return rc;
}