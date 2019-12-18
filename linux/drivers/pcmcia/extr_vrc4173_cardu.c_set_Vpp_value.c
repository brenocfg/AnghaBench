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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  VPP_0V ; 
 int /*<<< orphan*/  VPP_12V ; 
 int /*<<< orphan*/  VPP_VCC ; 

__attribute__((used)) static inline uint8_t set_Vpp_value(u_char Vpp)
{
	switch (Vpp) {
	case 33:
	case 50:
		return VPP_VCC;
	case 120:
		return VPP_12V;
	}

	return VPP_0V;
}