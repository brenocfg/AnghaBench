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
struct nvkm_device {TYPE_1__* func; } ;
struct io_mapping {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resource_size ) (struct nvkm_device*,int) ;int /*<<< orphan*/  (* resource_addr ) (struct nvkm_device*,int) ;} ;

/* Variables and functions */
 struct io_mapping* io_mapping_create_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_device*,int) ; 

__attribute__((used)) static inline struct io_mapping *
fbmem_init(struct nvkm_device *dev)
{
	return io_mapping_create_wc(dev->func->resource_addr(dev, 1),
				    dev->func->resource_size(dev, 1));
}