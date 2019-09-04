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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMAGE_START_MAGIC ; 
 int /*<<< orphan*/  IMAGE_TRAIL_MAGIC ; 
 int P1_SIZE ; 
 int /*<<< orphan*/  P1_START ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_length (struct hfi1_devdata*,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 void* strnstr (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_partition_platform_config(struct hfi1_devdata *dd, void **data,
					  u32 *size)
{
	void *buffer;
	void *p;
	u32 length;
	int ret;

	buffer = kmalloc(P1_SIZE, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	ret = read_length(dd, P1_START, P1_SIZE, buffer);
	if (ret) {
		kfree(buffer);
		return ret;
	}

	/* config partition is valid only if it starts with IMAGE_START_MAGIC */
	if (memcmp(buffer, IMAGE_START_MAGIC, strlen(IMAGE_START_MAGIC))) {
		kfree(buffer);
		return -ENOENT;
	}

	/* scan for image magic that may trail the actual data */
	p = strnstr(buffer, IMAGE_TRAIL_MAGIC, P1_SIZE);
	if (p)
		length = p - buffer;
	else
		length = P1_SIZE;

	*data = buffer;
	*size = length;
	return 0;
}