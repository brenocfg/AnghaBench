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
struct brcmnand_soc {int /*<<< orphan*/  (* prepare_data_bus ) (struct brcmnand_soc*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct brcmnand_soc*,int,int) ; 

__attribute__((used)) static inline void brcmnand_soc_data_bus_unprepare(struct brcmnand_soc *soc,
						   bool is_param)
{
	if (soc && soc->prepare_data_bus)
		soc->prepare_data_bus(soc, false, is_param);
}