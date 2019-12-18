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
struct rcar_csi2 {int /*<<< orphan*/  remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcsi2_enter_standby (struct rcar_csi2*) ; 
 int /*<<< orphan*/  rcsi2_exit_standby (struct rcar_csi2*) ; 
 int rcsi2_start_receiver (struct rcar_csi2*) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int rcsi2_start(struct rcar_csi2 *priv)
{
	int ret;

	rcsi2_exit_standby(priv);

	ret = rcsi2_start_receiver(priv);
	if (ret) {
		rcsi2_enter_standby(priv);
		return ret;
	}

	ret = v4l2_subdev_call(priv->remote, video, s_stream, 1);
	if (ret) {
		rcsi2_enter_standby(priv);
		return ret;
	}

	return 0;
}