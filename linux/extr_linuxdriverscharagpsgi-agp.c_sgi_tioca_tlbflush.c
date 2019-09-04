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
struct agp_memory {TYPE_1__* bridge; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  tioca_tlbflush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sgi_tioca_tlbflush(struct agp_memory *mem)
{
	tioca_tlbflush(mem->bridge->dev_private_data);
}