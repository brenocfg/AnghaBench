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
typedef  int /*<<< orphan*/  u_long ;
struct scb {int /*<<< orphan*/  io_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_set_resid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void ahc_set_residual(struct scb *scb, u_long resid)
{
	scsi_set_resid(scb->io_ctx, resid);
}