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
typedef  scalar_t__ u32 ;
struct octnic_ctrl_pkt {int /*<<< orphan*/  (* cb_fn ) (struct octnic_ctrl_pkt*) ;scalar_t__ status; } ;
struct octeon_soft_command {scalar_t__ ctxptr; } ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ FIRMWARE_STATUS_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  stub1 (struct octnic_ctrl_pkt*) ; 

__attribute__((used)) static void octnet_link_ctrl_callback(struct octeon_device *oct,
				      u32 status,
				      void *sc_ptr)
{
	struct octeon_soft_command *sc = (struct octeon_soft_command *)sc_ptr;
	struct octnic_ctrl_pkt *nctrl;

	nctrl = (struct octnic_ctrl_pkt *)sc->ctxptr;

	/* Call the callback function if status is zero (meaning OK) or status
	 * contains a firmware status code bigger than zero (meaning the
	 * firmware is reporting an error).
	 * If no response was expected, status is OK if the command was posted
	 * successfully.
	 */
	if ((!status || status > FIRMWARE_STATUS_CODE(0)) && nctrl->cb_fn) {
		nctrl->status = status;
		nctrl->cb_fn(nctrl);
	}

	octeon_free_soft_command(oct, sc);
}