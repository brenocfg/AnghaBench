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
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 scalar_t__ usbhs_pipe_is_dcp (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_read (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 __usbhsp_pipe_xxx_get(struct usbhs_pipe *pipe,
				 u16 dcp_reg, u16 pipe_reg)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	if (usbhs_pipe_is_dcp(pipe))
		return usbhs_read(priv, dcp_reg);
	else
		return usbhs_read(priv, pipe_reg);
}