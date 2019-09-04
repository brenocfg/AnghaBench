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
typedef  int /*<<< orphan*/  u32 ;
struct axon_msic {int /*<<< orphan*/  dcr_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcr_write (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void msic_dcr_write(struct axon_msic *msic, unsigned int dcr_n, u32 val)
{
	pr_devel("axon_msi: dcr_write(0x%x, 0x%x)\n", val, dcr_n);

	dcr_write(msic->dcr_host, dcr_n, val);
}