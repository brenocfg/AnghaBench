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
struct xc4000_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XREG_FRAME_LINES ; 
 int xc4000_readreg (struct xc4000_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xc_get_frame_lines(struct xc4000_priv *priv, u16 *frame_lines)
{
	return xc4000_readreg(priv, XREG_FRAME_LINES, frame_lines);
}