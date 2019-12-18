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
struct rcar_du_device {int dummy; } ;
struct rcar_du_crtc {int dsysr; scalar_t__ mmio_offset; struct rcar_du_device* dev; } ;

/* Variables and functions */
 scalar_t__ DSYSR ; 
 int /*<<< orphan*/  rcar_du_write (struct rcar_du_device*,scalar_t__,int) ; 

void rcar_du_crtc_dsysr_clr_set(struct rcar_du_crtc *rcrtc, u32 clr, u32 set)
{
	struct rcar_du_device *rcdu = rcrtc->dev;

	rcrtc->dsysr = (rcrtc->dsysr & ~clr) | set;
	rcar_du_write(rcdu, rcrtc->mmio_offset + DSYSR, rcrtc->dsysr);
}