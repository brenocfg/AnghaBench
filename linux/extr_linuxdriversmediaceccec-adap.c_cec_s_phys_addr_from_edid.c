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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct edid {int extensions; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int EDID_LENGTH ; 
 int /*<<< orphan*/  cec_get_edid_phys_addr (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_s_phys_addr (struct cec_adapter*,int /*<<< orphan*/ ,int) ; 

void cec_s_phys_addr_from_edid(struct cec_adapter *adap,
			       const struct edid *edid)
{
	u16 pa = CEC_PHYS_ADDR_INVALID;

	if (edid && edid->extensions)
		pa = cec_get_edid_phys_addr((const u8 *)edid,
				EDID_LENGTH * (edid->extensions + 1), NULL);
	cec_s_phys_addr(adap, pa, false);
}