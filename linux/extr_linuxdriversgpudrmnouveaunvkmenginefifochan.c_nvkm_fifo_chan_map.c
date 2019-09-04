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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_fifo_chan {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
typedef  enum nvkm_object_map { ____Placeholder_nvkm_object_map } nvkm_object_map ;

/* Variables and functions */
 int NVKM_OBJECT_MAP_IO ; 
 struct nvkm_fifo_chan* nvkm_fifo_chan (struct nvkm_object*) ; 

__attribute__((used)) static int
nvkm_fifo_chan_map(struct nvkm_object *object, void *argv, u32 argc,
		   enum nvkm_object_map *type, u64 *addr, u64 *size)
{
	struct nvkm_fifo_chan *chan = nvkm_fifo_chan(object);
	*type = NVKM_OBJECT_MAP_IO;
	*addr = chan->addr;
	*size = chan->size;
	return 0;
}