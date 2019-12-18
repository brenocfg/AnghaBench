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
struct wf_fcu_priv {int rpm_shift; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int wf_fcu_read_reg (struct wf_fcu_priv*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int wf_fcu_write_reg (struct wf_fcu_priv*,int,unsigned char*,int) ; 

__attribute__((used)) static int wf_fcu_init_chip(struct wf_fcu_priv *pv)
{
	unsigned char buf = 0xff;
	int rc;

	rc = wf_fcu_write_reg(pv, 0xe, &buf, 1);
	if (rc < 0)
		return -EIO;
	rc = wf_fcu_write_reg(pv, 0x2e, &buf, 1);
	if (rc < 0)
		return -EIO;
	rc = wf_fcu_read_reg(pv, 0, &buf, 1);
	if (rc < 0)
		return -EIO;
	pv->rpm_shift = (buf == 1) ? 2 : 3;

	pr_debug("wf_fcu: FCU Initialized, RPM fan shift is %d\n",
		 pv->rpm_shift);

	return 0;
}