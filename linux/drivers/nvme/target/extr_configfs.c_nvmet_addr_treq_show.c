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
struct TYPE_3__ {int treq; } ;
struct TYPE_4__ {TYPE_1__ disc_addr; } ;

/* Variables and functions */
 int NVME_TREQ_SECURE_CHANNEL_MASK ; 
#define  NVMF_TREQ_NOT_REQUIRED 130 
#define  NVMF_TREQ_NOT_SPECIFIED 129 
#define  NVMF_TREQ_REQUIRED 128 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 TYPE_2__* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_addr_treq_show(struct config_item *item,
		char *page)
{
	switch (to_nvmet_port(item)->disc_addr.treq &
		NVME_TREQ_SECURE_CHANNEL_MASK) {
	case NVMF_TREQ_NOT_SPECIFIED:
		return sprintf(page, "not specified\n");
	case NVMF_TREQ_REQUIRED:
		return sprintf(page, "required\n");
	case NVMF_TREQ_NOT_REQUIRED:
		return sprintf(page, "not required\n");
	default:
		return sprintf(page, "\n");
	}
}