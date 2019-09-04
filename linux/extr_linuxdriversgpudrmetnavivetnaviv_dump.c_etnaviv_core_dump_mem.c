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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct core_dump_iterator {scalar_t__ data; TYPE_1__* hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  iova; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_core_dump_header (struct core_dump_iterator*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 

__attribute__((used)) static void etnaviv_core_dump_mem(struct core_dump_iterator *iter, u32 type,
	void *ptr, size_t size, u64 iova)
{
	memcpy(iter->data, ptr, size);

	iter->hdr->iova = cpu_to_le64(iova);

	etnaviv_core_dump_header(iter, type, iter->data + size);
}