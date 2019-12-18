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
typedef  int uint8_t ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
#define  LPFC_FC_LA_SPEED_128G 136 
#define  LPFC_FC_LA_SPEED_16G 135 
#define  LPFC_FC_LA_SPEED_1G 134 
#define  LPFC_FC_LA_SPEED_256G 133 
#define  LPFC_FC_LA_SPEED_2G 132 
#define  LPFC_FC_LA_SPEED_32G 131 
#define  LPFC_FC_LA_SPEED_4G 130 
#define  LPFC_FC_LA_SPEED_64G 129 
#define  LPFC_FC_LA_SPEED_8G 128 
 int LPFC_LINK_SPEED_128GHZ ; 
 int LPFC_LINK_SPEED_16GHZ ; 
 int LPFC_LINK_SPEED_1GHZ ; 
 int LPFC_LINK_SPEED_256GHZ ; 
 int LPFC_LINK_SPEED_2GHZ ; 
 int LPFC_LINK_SPEED_32GHZ ; 
 int LPFC_LINK_SPEED_4GHZ ; 
 int LPFC_LINK_SPEED_64GHZ ; 
 int LPFC_LINK_SPEED_8GHZ ; 

__attribute__((used)) static uint8_t
lpfc_async_link_speed_to_read_top(struct lpfc_hba *phba, uint8_t speed_code)
{
	uint8_t port_speed;

	switch (speed_code) {
	case LPFC_FC_LA_SPEED_1G:
		port_speed = LPFC_LINK_SPEED_1GHZ;
		break;
	case LPFC_FC_LA_SPEED_2G:
		port_speed = LPFC_LINK_SPEED_2GHZ;
		break;
	case LPFC_FC_LA_SPEED_4G:
		port_speed = LPFC_LINK_SPEED_4GHZ;
		break;
	case LPFC_FC_LA_SPEED_8G:
		port_speed = LPFC_LINK_SPEED_8GHZ;
		break;
	case LPFC_FC_LA_SPEED_16G:
		port_speed = LPFC_LINK_SPEED_16GHZ;
		break;
	case LPFC_FC_LA_SPEED_32G:
		port_speed = LPFC_LINK_SPEED_32GHZ;
		break;
	case LPFC_FC_LA_SPEED_64G:
		port_speed = LPFC_LINK_SPEED_64GHZ;
		break;
	case LPFC_FC_LA_SPEED_128G:
		port_speed = LPFC_LINK_SPEED_128GHZ;
		break;
	case LPFC_FC_LA_SPEED_256G:
		port_speed = LPFC_LINK_SPEED_256GHZ;
		break;
	default:
		port_speed = 0;
		break;
	}

	return port_speed;
}