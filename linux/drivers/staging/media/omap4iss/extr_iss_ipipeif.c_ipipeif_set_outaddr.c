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
typedef  int u32 ;
struct iss_ipipeif_device {int dummy; } ;
struct iss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISIF_CADL ; 
 int ISIF_CADL_MASK ; 
 int /*<<< orphan*/  ISIF_CADU ; 
 int ISIF_CADU_MASK ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_ISIF ; 
 int /*<<< orphan*/  iss_reg_write (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct iss_device* to_iss_device (struct iss_ipipeif_device*) ; 

__attribute__((used)) static void ipipeif_set_outaddr(struct iss_ipipeif_device *ipipeif, u32 addr)
{
	struct iss_device *iss = to_iss_device(ipipeif);

	/* Save address split in Base Address H & L */
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CADU,
		      (addr >> (16 + 5)) & ISIF_CADU_MASK);
	iss_reg_write(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CADL,
		      (addr >> 5) & ISIF_CADL_MASK);
}