#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cap; } ;
typedef  TYPE_1__ vrc4173_socket_t ;
typedef  int /*<<< orphan*/  socket_cap_t ;

/* Variables and functions */
 TYPE_1__* cardu_sockets ; 

__attribute__((used)) static int cardu_inquire_socket(unsigned int sock, socket_cap_t *cap)
{
	vrc4173_socket_t *socket = &cardu_sockets[sock];

	*cap = socket->cap;

	return 0;
}