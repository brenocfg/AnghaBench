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
struct tb_xdomain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  start_handshake (struct tb_xdomain*) ; 

void tb_xdomain_add(struct tb_xdomain *xd)
{
	/* Start exchanging properties with the other host */
	start_handshake(xd);
}