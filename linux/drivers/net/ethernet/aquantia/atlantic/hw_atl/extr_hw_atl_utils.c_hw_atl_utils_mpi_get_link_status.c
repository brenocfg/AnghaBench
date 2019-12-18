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
typedef  int u32 ;
struct aq_hw_link_status_s {unsigned int mbps; } ;
struct aq_hw_s {struct aq_hw_link_status_s aq_link_status; } ;

/* Variables and functions */
 int EBUSY ; 
#define  HAL_ATLANTIC_RATE_100M 133 
#define  HAL_ATLANTIC_RATE_10G 132 
#define  HAL_ATLANTIC_RATE_1G 131 
#define  HAL_ATLANTIC_RATE_2GS 130 
#define  HAL_ATLANTIC_RATE_5G 129 
#define  HAL_ATLANTIC_RATE_5GSR 128 
 int HW_ATL_MPI_SPEED_SHIFT ; 
 int hw_atl_utils_mpi_get_state (struct aq_hw_s*) ; 

int hw_atl_utils_mpi_get_link_status(struct aq_hw_s *self)
{
	u32 cp0x036C = hw_atl_utils_mpi_get_state(self);
	u32 link_speed_mask = cp0x036C >> HW_ATL_MPI_SPEED_SHIFT;
	struct aq_hw_link_status_s *link_status = &self->aq_link_status;

	if (!link_speed_mask) {
		link_status->mbps = 0U;
	} else {
		switch (link_speed_mask) {
		case HAL_ATLANTIC_RATE_10G:
			link_status->mbps = 10000U;
			break;

		case HAL_ATLANTIC_RATE_5G:
		case HAL_ATLANTIC_RATE_5GSR:
			link_status->mbps = 5000U;
			break;

		case HAL_ATLANTIC_RATE_2GS:
			link_status->mbps = 2500U;
			break;

		case HAL_ATLANTIC_RATE_1G:
			link_status->mbps = 1000U;
			break;

		case HAL_ATLANTIC_RATE_100M:
			link_status->mbps = 100U;
			break;

		default:
			return -EBUSY;
		}
	}

	return 0;
}