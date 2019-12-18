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
struct iommu_group {TYPE_1__* default_domain; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  IOMMU_DOMAIN_BLOCKED 131 
#define  IOMMU_DOMAIN_DMA 130 
#define  IOMMU_DOMAIN_IDENTITY 129 
#define  IOMMU_DOMAIN_UNMANAGED 128 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t iommu_group_show_type(struct iommu_group *group,
				     char *buf)
{
	char *type = "unknown\n";

	if (group->default_domain) {
		switch (group->default_domain->type) {
		case IOMMU_DOMAIN_BLOCKED:
			type = "blocked\n";
			break;
		case IOMMU_DOMAIN_IDENTITY:
			type = "identity\n";
			break;
		case IOMMU_DOMAIN_UNMANAGED:
			type = "unmanaged\n";
			break;
		case IOMMU_DOMAIN_DMA:
			type = "DMA\n";
			break;
		}
	}
	strcpy(buf, type);

	return strlen(type);
}