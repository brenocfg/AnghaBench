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
struct enetc_si {int dummy; } ;
struct enetc_cbd {int cls; int /*<<< orphan*/  index; int /*<<< orphan*/  status_flags; } ;
typedef  int /*<<< orphan*/  cbd ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_CBD_FLAGS_SF ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int enetc_send_cmd (struct enetc_si*,struct enetc_cbd*) ; 
 int /*<<< orphan*/  memset (struct enetc_cbd*,int /*<<< orphan*/ ,int) ; 

int enetc_clear_mac_flt_entry(struct enetc_si *si, int index)
{
	struct enetc_cbd cbd;

	memset(&cbd, 0, sizeof(cbd));

	cbd.cls = 1;
	cbd.status_flags = ENETC_CBD_FLAGS_SF;
	cbd.index = cpu_to_le16(index);

	return enetc_send_cmd(si, &cbd);
}