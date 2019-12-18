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
typedef  int u32 ;
struct u132 {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 TYPE_1__ roothub ; 
 int u132_read_pcimem (struct u132*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int u132_roothub_status(struct u132 *u132, __le32 *desc)
{
	u32 rh_status = -1;
	int ret_status = u132_read_pcimem(u132, roothub.status, &rh_status);
	*desc = cpu_to_le32(rh_status);
	return ret_status;
}