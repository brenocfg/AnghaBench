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
typedef  scalar_t__ u32 ;
struct m5mols_info {int /*<<< orphan*/  sd; TYPE_1__* iso; } ;
struct TYPE_2__ {scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ISO ; 
 int m5mols_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int m5mols_set_iso(struct m5mols_info *info, int auto_iso)
{
	u32 iso = auto_iso ? 0 : info->iso->val + 1;

	return m5mols_write(&info->sd, AE_ISO, iso);
}