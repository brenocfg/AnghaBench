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
typedef  int u16 ;
struct goodix_chip_data {int dummy; } ;

/* Variables and functions */
 struct goodix_chip_data const gt1x_chip_data ; 
 struct goodix_chip_data const gt911_chip_data ; 
 struct goodix_chip_data const gt967_chip_data ; 
 struct goodix_chip_data const gt9x_chip_data ; 

__attribute__((used)) static const struct goodix_chip_data *goodix_get_chip_data(u16 id)
{
	switch (id) {
	case 1151:
		return &gt1x_chip_data;

	case 911:
	case 9271:
	case 9110:
	case 927:
	case 928:
		return &gt911_chip_data;

	case 912:
	case 967:
		return &gt967_chip_data;

	default:
		return &gt9x_chip_data;
	}
}