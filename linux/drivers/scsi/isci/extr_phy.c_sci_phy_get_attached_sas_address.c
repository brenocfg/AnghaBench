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
struct sci_sas_address {int dummy; } ;
struct sas_identify_frame {int /*<<< orphan*/  sas_addr; } ;
struct TYPE_2__ {struct sas_identify_frame iaf; } ;
struct isci_phy {TYPE_1__ frame_rcvd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  memcpy (struct sci_sas_address*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sci_phy_get_attached_sas_address(struct isci_phy *iphy, struct sci_sas_address *sas)
{
	struct sas_identify_frame *iaf;

	iaf = &iphy->frame_rcvd.iaf;
	memcpy(sas, iaf->sas_addr, SAS_ADDR_SIZE);
}