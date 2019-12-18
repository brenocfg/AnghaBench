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
struct usbhs_priv {int dummy; } ;
struct renesas_usbhs_driver_pipe_config {int dummy; } ;

/* Variables and functions */
 struct renesas_usbhs_driver_pipe_config* pipe_configs ; 
 struct renesas_usbhs_driver_pipe_config* usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct renesas_usbhs_driver_pipe_config
*usbhsp_get_pipe_config(struct usbhs_priv *priv, int pipe_num)
{
	struct renesas_usbhs_driver_pipe_config *pipe_configs =
					usbhs_get_dparam(priv, pipe_configs);

	return &pipe_configs[pipe_num];
}