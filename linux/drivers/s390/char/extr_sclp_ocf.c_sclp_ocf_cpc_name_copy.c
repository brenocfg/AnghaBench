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

/* Variables and functions */
 int /*<<< orphan*/  OCF_LENGTH_CPC_NAME ; 
 int /*<<< orphan*/  cpc_name ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sclp_ocf_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void sclp_ocf_cpc_name_copy(char *dst)
{
	spin_lock_irq(&sclp_ocf_lock);
	memcpy(dst, cpc_name, OCF_LENGTH_CPC_NAME);
	spin_unlock_irq(&sclp_ocf_lock);
}