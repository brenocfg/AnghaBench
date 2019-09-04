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
struct enc28j60_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISTAT ; 
 int /*<<< orphan*/  MISTAT_BUSY ; 
 scalar_t__ poll_ready (struct enc28j60_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_phy_ready(struct enc28j60_net *priv)
{
	return poll_ready(priv, MISTAT, MISTAT_BUSY, 0) ? 0 : 1;
}