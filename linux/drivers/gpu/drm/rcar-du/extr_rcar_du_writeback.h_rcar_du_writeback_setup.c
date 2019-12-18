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
struct vsp1_du_writeback_config {int dummy; } ;
struct rcar_du_crtc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
rcar_du_writeback_setup(struct rcar_du_crtc *rcrtc,
			struct vsp1_du_writeback_config *cfg)
{
}