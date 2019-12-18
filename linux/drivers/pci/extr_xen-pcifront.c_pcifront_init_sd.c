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
struct TYPE_2__ {unsigned int domain; int /*<<< orphan*/  node; } ;
struct pcifront_sd {struct pcifront_device* pdev; TYPE_1__ sd; } ;
struct pcifront_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  first_online_node ; 

__attribute__((used)) static inline void pcifront_init_sd(struct pcifront_sd *sd,
				    unsigned int domain, unsigned int bus,
				    struct pcifront_device *pdev)
{
	/* Because we do not expose that information via XenBus. */
	sd->sd.node = first_online_node;
	sd->sd.domain = domain;
	sd->pdev = pdev;
}