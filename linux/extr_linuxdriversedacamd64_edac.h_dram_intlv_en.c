#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct amd64_pvt {int fam; int model; TYPE_2__* ranges; int /*<<< orphan*/  F1; } ;
struct TYPE_3__ {int lo; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRAM_CONT_LIMIT ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static inline u8 dram_intlv_en(struct amd64_pvt *pvt, unsigned int i)
{
	if (pvt->fam == 0x15 && pvt->model >= 0x30) {
		u32 tmp;
		amd64_read_pci_cfg(pvt->F1, DRAM_CONT_LIMIT, &tmp);
		return (u8) tmp & 0xF;
	}
	return (u8) (pvt->ranges[i].base.lo >> 8) & 0x7;
}