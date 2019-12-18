#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int adrfam; } ;
struct TYPE_4__ {TYPE_1__ disc_addr; } ;

/* Variables and functions */
#define  NVMF_ADDR_FAMILY_FC 131 
#define  NVMF_ADDR_FAMILY_IB 130 
#define  NVMF_ADDR_FAMILY_IP4 129 
#define  NVMF_ADDR_FAMILY_IP6 128 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 TYPE_2__* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_addr_adrfam_show(struct config_item *item,
		char *page)
{
	switch (to_nvmet_port(item)->disc_addr.adrfam) {
	case NVMF_ADDR_FAMILY_IP4:
		return sprintf(page, "ipv4\n");
	case NVMF_ADDR_FAMILY_IP6:
		return sprintf(page, "ipv6\n");
	case NVMF_ADDR_FAMILY_IB:
		return sprintf(page, "ib\n");
	case NVMF_ADDR_FAMILY_FC:
		return sprintf(page, "fc\n");
	default:
		return sprintf(page, "\n");
	}
}