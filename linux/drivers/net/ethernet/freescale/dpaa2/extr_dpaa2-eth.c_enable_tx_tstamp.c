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
struct dpaa2_fd {int dummy; } ;
struct dpaa2_faead {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int DPAA2_FAEAD_A2V ; 
 int DPAA2_FAEAD_UPD ; 
 int DPAA2_FAEAD_UPDV ; 
 int DPAA2_FD_CTRL_ASAL ; 
 int DPAA2_FD_FRC_FAEADV ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int dpaa2_fd_get_ctrl (struct dpaa2_fd*) ; 
 int dpaa2_fd_get_frc (struct dpaa2_fd*) ; 
 int /*<<< orphan*/  dpaa2_fd_set_ctrl (struct dpaa2_fd*,int) ; 
 int /*<<< orphan*/  dpaa2_fd_set_frc (struct dpaa2_fd*,int) ; 
 struct dpaa2_faead* dpaa2_get_faead (void*,int) ; 

__attribute__((used)) static void enable_tx_tstamp(struct dpaa2_fd *fd, void *buf_start)
{
	struct dpaa2_faead *faead;
	u32 ctrl, frc;

	/* Mark the egress frame annotation area as valid */
	frc = dpaa2_fd_get_frc(fd);
	dpaa2_fd_set_frc(fd, frc | DPAA2_FD_FRC_FAEADV);

	/* Set hardware annotation size */
	ctrl = dpaa2_fd_get_ctrl(fd);
	dpaa2_fd_set_ctrl(fd, ctrl | DPAA2_FD_CTRL_ASAL);

	/* enable UPD (update prepanded data) bit in FAEAD field of
	 * hardware frame annotation area
	 */
	ctrl = DPAA2_FAEAD_A2V | DPAA2_FAEAD_UPDV | DPAA2_FAEAD_UPD;
	faead = dpaa2_get_faead(buf_start, true);
	faead->ctrl = cpu_to_le32(ctrl);
}