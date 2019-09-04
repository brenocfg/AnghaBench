#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nand_sdr_timings {int dummy; } ;
struct TYPE_4__ {struct nand_sdr_timings const sdr; } ;
struct TYPE_5__ {TYPE_1__ timings; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  EINVAL ; 
 struct nand_sdr_timings const* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_2__* onfi_sdr_timings ; 

const struct nand_sdr_timings *onfi_async_timing_mode_to_sdr_timings(int mode)
{
	if (mode < 0 || mode >= ARRAY_SIZE(onfi_sdr_timings))
		return ERR_PTR(-EINVAL);

	return &onfi_sdr_timings[mode].timings.sdr;
}