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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {size_t size; int /*<<< orphan*/ * data; } ;
struct nvkm_hwsq {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
hwsq_cmd(struct nvkm_hwsq *hwsq, int size, u8 data[])
{
	memcpy(&hwsq->c.data[hwsq->c.size], data, size * sizeof(data[0]));
	hwsq->c.size += size;
}