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
typedef  int u8 ;
struct ocrdma_dev {int dummy; } ;

/* Variables and functions */
 int IB_SPEED_DDR ; 
 int IB_SPEED_QDR ; 
 int IB_SPEED_SDR ; 
 int IB_WIDTH_1X ; 
 int IB_WIDTH_4X ; 
#define  OCRDMA_PHYS_LINK_SPEED_10GBPS 131 
#define  OCRDMA_PHYS_LINK_SPEED_1GBPS 130 
#define  OCRDMA_PHYS_LINK_SPEED_20GBPS 129 
#define  OCRDMA_PHYS_LINK_SPEED_40GBPS 128 
 int OCRDMA_PHYS_LINK_SPEED_ZERO ; 
 int ocrdma_mbx_get_link_speed (struct ocrdma_dev*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void get_link_speed_and_width(struct ocrdma_dev *dev,
					    u8 *ib_speed, u8 *ib_width)
{
	int status;
	u8 speed;

	status = ocrdma_mbx_get_link_speed(dev, &speed, NULL);
	if (status)
		speed = OCRDMA_PHYS_LINK_SPEED_ZERO;

	switch (speed) {
	case OCRDMA_PHYS_LINK_SPEED_1GBPS:
		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
		break;

	case OCRDMA_PHYS_LINK_SPEED_10GBPS:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_1X;
		break;

	case OCRDMA_PHYS_LINK_SPEED_20GBPS:
		*ib_speed = IB_SPEED_DDR;
		*ib_width = IB_WIDTH_4X;
		break;

	case OCRDMA_PHYS_LINK_SPEED_40GBPS:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_4X;
		break;

	default:
		/* Unsupported */
		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
	}
}