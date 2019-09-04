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
 int EINVAL ; 
 int HALIBUT_ID ; 
 int SWORDFISH_ID ; 
 int TRITON_ID ; 
#define  tmd2671 137 
#define  tmd2672 136 
#define  tmd2771 135 
#define  tmd2772 134 
#define  tsl2571 133 
#define  tsl2572 132 
#define  tsl2671 131 
#define  tsl2672 130 
#define  tsl2771 129 
#define  tsl2772 128 

__attribute__((used)) static int tsl2772_device_id_verif(int id, int target)
{
	switch (target) {
	case tsl2571:
	case tsl2671:
	case tsl2771:
		return (id & 0xf0) == TRITON_ID;
	case tmd2671:
	case tmd2771:
		return (id & 0xf0) == HALIBUT_ID;
	case tsl2572:
	case tsl2672:
	case tmd2672:
	case tsl2772:
	case tmd2772:
		return (id & 0xf0) == SWORDFISH_ID;
	}

	return -EINVAL;
}