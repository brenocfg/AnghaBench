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
struct iscsi_np {scalar_t__ np_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  sock_release (scalar_t__) ; 

__attribute__((used)) static void iscsit_free_np(struct iscsi_np *np)
{
	if (np->np_socket)
		sock_release(np->np_socket);
}