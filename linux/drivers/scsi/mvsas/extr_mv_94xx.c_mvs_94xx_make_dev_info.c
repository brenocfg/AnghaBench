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
struct sas_identify_frame {int dev_type; scalar_t__ phy_id; scalar_t__ ssp_tport; scalar_t__ smp_tport; scalar_t__ stp_tport; scalar_t__ ssp_iport; scalar_t__ smp_iport; scalar_t__ stp_iport; } ;

/* Variables and functions */
 int PORT_DEV_SMP_INIT ; 
 int PORT_DEV_SMP_TRGT ; 
 int PORT_DEV_SSP_INIT ; 
 int PORT_DEV_SSP_TRGT ; 
 int PORT_DEV_STP_INIT ; 
 int PORT_DEV_STP_TRGT ; 

__attribute__((used)) static u32 mvs_94xx_make_dev_info(struct sas_identify_frame *id)
{
	u32 att_dev_info = 0;

	att_dev_info |= id->dev_type;
	if (id->stp_iport)
		att_dev_info |= PORT_DEV_STP_INIT;
	if (id->smp_iport)
		att_dev_info |= PORT_DEV_SMP_INIT;
	if (id->ssp_iport)
		att_dev_info |= PORT_DEV_SSP_INIT;
	if (id->stp_tport)
		att_dev_info |= PORT_DEV_STP_TRGT;
	if (id->smp_tport)
		att_dev_info |= PORT_DEV_SMP_TRGT;
	if (id->ssp_tport)
		att_dev_info |= PORT_DEV_SSP_TRGT;

	att_dev_info |= (u32)id->phy_id<<24;
	return att_dev_info;
}