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
struct zorro_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct zorro_dev {TYPE_1__ resource; } ;

/* Variables and functions */
 int EBUSY ; 
 int hydra_init (struct zorro_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int hydra_init_one(struct zorro_dev *z,
			  const struct zorro_device_id *ent)
{
    int err;

    if (!request_mem_region(z->resource.start, 0x10000, "Hydra"))
	return -EBUSY;
    if ((err = hydra_init(z))) {
	release_mem_region(z->resource.start, 0x10000);
	return -EBUSY;
    }
    return 0;
}