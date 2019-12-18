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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 struct socket* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct socket*) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct socket* tap_get_socket (struct file*) ; 
 struct socket* tun_get_socket (struct file*) ; 

__attribute__((used)) static struct socket *get_tap_socket(int fd)
{
	struct file *file = fget(fd);
	struct socket *sock;

	if (!file)
		return ERR_PTR(-EBADF);
	sock = tun_get_socket(file);
	if (!IS_ERR(sock))
		return sock;
	sock = tap_get_socket(file);
	if (IS_ERR(sock))
		fput(file);
	return sock;
}