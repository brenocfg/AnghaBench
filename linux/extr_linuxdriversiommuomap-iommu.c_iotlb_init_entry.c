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
typedef  void* u32 ;
struct iotlb_entry {int pgsz; scalar_t__ mixed; int /*<<< orphan*/  elsz; int /*<<< orphan*/  endian; int /*<<< orphan*/  valid; void* pa; void* da; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_CAM_V ; 
 int /*<<< orphan*/  MMU_RAM_ELSZ_8 ; 
 int /*<<< orphan*/  MMU_RAM_ENDIAN_LITTLE ; 
 void* iopgsz_to_bytes (int) ; 
 int /*<<< orphan*/  memset (struct iotlb_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 iotlb_init_entry(struct iotlb_entry *e, u32 da, u32 pa, int pgsz)
{
	memset(e, 0, sizeof(*e));

	e->da		= da;
	e->pa		= pa;
	e->valid	= MMU_CAM_V;
	e->pgsz		= pgsz;
	e->endian	= MMU_RAM_ENDIAN_LITTLE;
	e->elsz		= MMU_RAM_ELSZ_8;
	e->mixed	= 0;

	return iopgsz_to_bytes(e->pgsz);
}