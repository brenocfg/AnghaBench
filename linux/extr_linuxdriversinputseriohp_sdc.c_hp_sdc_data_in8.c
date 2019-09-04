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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  data_io; } ;

/* Variables and functions */
 TYPE_1__ hp_sdc ; 
 int /*<<< orphan*/  sdc_readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t hp_sdc_data_in8(void)
{
	return sdc_readb(hp_sdc.data_io);
}