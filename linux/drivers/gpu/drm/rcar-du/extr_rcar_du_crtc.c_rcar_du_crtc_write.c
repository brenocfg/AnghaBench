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
struct rcar_du_device {int dummy; } ;
struct rcar_du_crtc {scalar_t__ mmio_offset; struct rcar_du_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcar_du_write (struct rcar_du_device*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void rcar_du_crtc_write(struct rcar_du_crtc *rcrtc, u32 reg, u32 data)
{
	struct rcar_du_device *rcdu = rcrtc->dev;

	rcar_du_write(rcdu, rcrtc->mmio_offset + reg, data);
}