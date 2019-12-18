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
typedef  int /*<<< orphan*/  u8 ;
struct b53_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* serdes_map_lane ) (struct b53_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B53_INVALID_LANE ; 
 int /*<<< orphan*/  stub1 (struct b53_device*,int) ; 

__attribute__((used)) static inline u8 b53_serdes_map_lane(struct b53_device *dev, int port)
{
	if (!dev->ops->serdes_map_lane)
		return B53_INVALID_LANE;

	return dev->ops->serdes_map_lane(dev, port);
}