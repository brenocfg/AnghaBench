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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FSP_PAGE_0B ; 
 int /*<<< orphan*/  FSP_PAGE_DEFAULT ; 
 int /*<<< orphan*/  FSP_REG_SN0 ; 
 int /*<<< orphan*/  FSP_REG_SN1 ; 
 int /*<<< orphan*/  FSP_REG_SN2 ; 
 scalar_t__ fsp_page_reg_write (struct psmouse*,int /*<<< orphan*/ ) ; 
 scalar_t__ fsp_reg_read (struct psmouse*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fsp_get_sn(struct psmouse *psmouse, int *sn)
{
	int v0, v1, v2;
	int rc = -EIO;

	/* production number since Cx is available at: 0x0b40 ~ 0x0b42 */
	if (fsp_page_reg_write(psmouse, FSP_PAGE_0B))
		goto out;
	if (fsp_reg_read(psmouse, FSP_REG_SN0, &v0))
		goto out;
	if (fsp_reg_read(psmouse, FSP_REG_SN1, &v1))
		goto out;
	if (fsp_reg_read(psmouse, FSP_REG_SN2, &v2))
		goto out;
	*sn = (v0 << 16) | (v1 << 8) | v2;
	rc = 0;
out:
	fsp_page_reg_write(psmouse, FSP_PAGE_DEFAULT);
	return rc;
}