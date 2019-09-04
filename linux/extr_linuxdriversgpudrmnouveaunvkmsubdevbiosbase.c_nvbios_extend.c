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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {scalar_t__ size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

int
nvbios_extend(struct nvkm_bios *bios, u32 length)
{
	if (bios->size < length) {
		u8 *prev = bios->data;
		if (!(bios->data = kmalloc(length, GFP_KERNEL))) {
			bios->data = prev;
			return -ENOMEM;
		}
		memcpy(bios->data, prev, bios->size);
		bios->size = length;
		kfree(prev);
		return 1;
	}
	return 0;
}