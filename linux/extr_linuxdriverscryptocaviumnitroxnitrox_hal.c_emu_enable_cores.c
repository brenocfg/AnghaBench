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
struct TYPE_4__ {int enable; } ;
union emu_se_enable {scalar_t__ value; TYPE_2__ s; } ;
struct TYPE_3__ {int enable; } ;
union emu_ae_enable {scalar_t__ value; TYPE_1__ s; } ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_AE_ENABLEX (int) ; 
 int /*<<< orphan*/  EMU_SE_ENABLEX (int) ; 
 int NR_CLUSTERS ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void emu_enable_cores(struct nitrox_device *ndev)
{
	union emu_se_enable emu_se;
	union emu_ae_enable emu_ae;
	int i;

	/* AE cores 20 per cluster */
	emu_ae.value = 0;
	emu_ae.s.enable = 0xfffff;

	/* SE cores 16 per cluster */
	emu_se.value = 0;
	emu_se.s.enable = 0xffff;

	/* enable per cluster cores */
	for (i = 0; i < NR_CLUSTERS; i++) {
		nitrox_write_csr(ndev, EMU_AE_ENABLEX(i), emu_ae.value);
		nitrox_write_csr(ndev, EMU_SE_ENABLEX(i), emu_se.value);
	}
}