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

/* Variables and functions */
#define  TPS65090_REGULATOR_DCDC1 130 
#define  TPS65090_REGULATOR_DCDC2 129 
#define  TPS65090_REGULATOR_DCDC3 128 

__attribute__((used)) static inline bool is_dcdc(int id)
{
	switch (id) {
	case TPS65090_REGULATOR_DCDC1:
	case TPS65090_REGULATOR_DCDC2:
	case TPS65090_REGULATOR_DCDC3:
		return true;
	default:
		return false;
	}
}