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
struct etherh_priv {unsigned char ctrl; int /*<<< orphan*/  ctrl_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void etherh_set_ctrl(struct etherh_priv *eh, unsigned char mask)
{
	unsigned char ctrl = eh->ctrl | mask;
	eh->ctrl = ctrl;
	writeb(ctrl, eh->ctrl_port);
}