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
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_2__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct iforce {int /*<<< orphan*/  mem_mutex; TYPE_1__ device_memory; } ;
typedef  int /*<<< orphan*/  __s16 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  FF_CMD_MAGNITUDE ; 
 unsigned char HI (int /*<<< orphan*/ ) ; 
 unsigned char HIFIX80 (int /*<<< orphan*/ ) ; 
 unsigned char LO (int /*<<< orphan*/ ) ; 
 scalar_t__ allocate_resource (TYPE_1__*,struct resource*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iforce_dump_packet (struct iforce*,char*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  iforce_send_packet (struct iforce*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int make_magnitude_modifier(struct iforce* iforce,
	struct resource* mod_chunk, int no_alloc, __s16 level)
{
	unsigned char data[3];

	if (!no_alloc) {
		mutex_lock(&iforce->mem_mutex);
		if (allocate_resource(&(iforce->device_memory), mod_chunk, 2,
			iforce->device_memory.start, iforce->device_memory.end, 2L,
			NULL, NULL)) {
			mutex_unlock(&iforce->mem_mutex);
			return -ENOSPC;
		}
		mutex_unlock(&iforce->mem_mutex);
	}

	data[0] = LO(mod_chunk->start);
	data[1] = HI(mod_chunk->start);
	data[2] = HIFIX80(level);

	iforce_send_packet(iforce, FF_CMD_MAGNITUDE, data);

	iforce_dump_packet(iforce, "magnitude", FF_CMD_MAGNITUDE, data);
	return 0;
}