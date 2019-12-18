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
typedef  int /*<<< orphan*/  u16 ;
struct pmic8xxx_kp {int /*<<< orphan*/ * keystate; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  new_state ;

/* Variables and functions */
 int EINVAL ; 
 int PM8XXX_MAX_ROWS ; 
 int /*<<< orphan*/  __pmic8xxx_kp_scan_matrix (struct pmic8xxx_kp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmic8xxx_detect_ghost_keys (struct pmic8xxx_kp*,int /*<<< orphan*/ *) ; 
 int pmic8xxx_kp_read_matrix (struct pmic8xxx_kp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmic8xxx_kp_scan_matrix(struct pmic8xxx_kp *kp, unsigned int events)
{
	u16 new_state[PM8XXX_MAX_ROWS];
	u16 old_state[PM8XXX_MAX_ROWS];
	int rc;

	switch (events) {
	case 0x1:
		rc = pmic8xxx_kp_read_matrix(kp, new_state, NULL);
		if (rc < 0)
			return rc;

		/* detecting ghost key is not an error */
		if (pmic8xxx_detect_ghost_keys(kp, new_state))
			return 0;
		__pmic8xxx_kp_scan_matrix(kp, new_state, kp->keystate);
		memcpy(kp->keystate, new_state, sizeof(new_state));
	break;
	case 0x3: /* two events - eventcounter is gray-coded */
		rc = pmic8xxx_kp_read_matrix(kp, new_state, old_state);
		if (rc < 0)
			return rc;

		__pmic8xxx_kp_scan_matrix(kp, old_state, kp->keystate);
		__pmic8xxx_kp_scan_matrix(kp, new_state, old_state);
		memcpy(kp->keystate, new_state, sizeof(new_state));
	break;
	case 0x2:
		dev_dbg(kp->dev, "Some key events were lost\n");
		rc = pmic8xxx_kp_read_matrix(kp, new_state, old_state);
		if (rc < 0)
			return rc;
		__pmic8xxx_kp_scan_matrix(kp, old_state, kp->keystate);
		__pmic8xxx_kp_scan_matrix(kp, new_state, old_state);
		memcpy(kp->keystate, new_state, sizeof(new_state));
	break;
	default:
		rc = -EINVAL;
	}
	return rc;
}