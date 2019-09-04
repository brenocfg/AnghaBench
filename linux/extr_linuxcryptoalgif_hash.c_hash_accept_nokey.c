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
struct socket {int dummy; } ;

/* Variables and functions */
 int hash_accept (struct socket*,struct socket*,int,int) ; 
 int hash_check_key (struct socket*) ; 

__attribute__((used)) static int hash_accept_nokey(struct socket *sock, struct socket *newsock,
			     int flags, bool kern)
{
	int err;

	err = hash_check_key(sock);
	if (err)
		return err;

	return hash_accept(sock, newsock, flags, kern);
}